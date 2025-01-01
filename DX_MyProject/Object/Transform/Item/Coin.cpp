#include "framework.h"

vector<shared_ptr<const Frame>>& Coin::GetCoinFrames()
{
	static vector<shared_ptr<const Frame>> coinFrames;
	return coinFrames;
}

int& Coin::GetCoinUseCnt()
{
	static int coinUseCnt = 0;
	return coinUseCnt;
}

Coin::Coin()
	:Item()
	, speed(100.0f)
	, idleSPD(10.0f)
	, changeTime(0.5f)
	, nowTime(0.5f)
	, isUp(false)
	,coinAmount(0)
{
	if (GetCoinFrames().empty())
	{
		InitFrame();
	}

	clips.emplace_back(make_shared<Clip>(GetCoinFrames(), Clip::CLIP_TYPE::LOOP, 1.0f / 6.0f));

	// collider
	colliders.push_back(new RectCollider(Vector2(15.0f, 15.0f) * 2.0f));
	collider = colliders[0];
	collider->pos = pos;

	clipIdx = 0;
	scale = clips[clipIdx]->GetFrameSize() * collider->Size() / clips[clipIdx]->GetFrameOriginSize();

	id = ITEM_ID::COIN;
	type = ITEM_TYPE::COIN;

	is_active = false;
	collider->SetActive(false);

	++GetCoinUseCnt();
}

Coin::~Coin()
{
	for (auto c : colliders)
	{
		if (c != nullptr)
			delete c;
	}

	if ((--GetCoinUseCnt()) == 0)
	{
		ClearFrame();
	}
}

void Coin::Update()
{
	if (!is_active)return;

	switch (state)
	{
	case Item::ITEM_STATE::IDLE:
	{
		nowTime += DELTA;
		if (isUp)
			moveDir = Vector2(0, -1.0f);
		else
			moveDir = Vector2(0, 1.0f);

		if (nowTime >= changeTime)
		{
			isUp = !isUp;
			nowTime -= changeTime;
		}

		if (addtionalDir.GetLength() > 0.1f)
			moveDir = (moveDir+addtionalDir).Normalized();
		pos += moveDir * idleSPD * DELTA;
	}
	break;
	case Item::ITEM_STATE::ACTIVE:
	{
		pos = LERP(pos, target->pos, speed / 30.0f * DELTA);
	}
	break;
	case Item::ITEM_STATE::USED:
	{
		// 코인 수치를 관리할 곳에 값을 증가시킴 - 미구현
		ItemSpawner::Get()->nowCoinValue += coinAmount;
		is_active = false;
		collider->SetActive(false);
	}
	break;
	default:
		break;
	}

	scale = clips[clipIdx]->GetFrameSize() * collider->Size() / clips[clipIdx]->GetFrameOriginSize();
	clips[clipIdx]->Update();

	WorldUpdate();

	collider->pos = pos;
	collider->WorldUpdate();
}

void Coin::Render()
{
	if (!is_active)return;

	VS->Set();
	PS->Set();

	WB->SetVS(0);
	CB->SetPS(0);

	clips[0]->Render();
	collider->Render();
}

void Coin::PostRender()
{
	if (!is_active)return;
}

void Coin::SetStatus(Item::ITEM_ID id, int value)
{
	this->id = id;
	coinAmount = value;
}

void Coin::SetPos(Vector2 pos)
{
	this->pos = pos;
	collider->pos = pos;
}

void Coin::InitFrame()
{
	auto& coinFrames = GetCoinFrames();
	if (!(coinFrames.empty())) return;

	wstring file = L"Textures/Item/PC Computer - HoloCure - Save the Fans - Pickups_rm_bg.png";

	// coin clip
	Vector2 initPos(4, 300);
	for (int i = 0; i < 8; i++)
	{
		coinFrames.emplace_back(make_shared<const Frame>(file, initPos.x + 17 * i, 300.0f, 15.0f, 15.0f));
	}
}

void Coin::ClearFrame()
{
	GetCoinFrames().clear();
}

void Coin::Respawn()
{
	state = ITEM_STATE::IDLE;

	WorldUpdate();
	collider->pos = pos;
	collider->WorldUpdate();

	scale = clips[clipIdx]->GetFrameSize() * collider->Size() /
		clips[clipIdx]->GetFrameOriginSize();

	is_active = true;
	collider->SetActive(true);
}