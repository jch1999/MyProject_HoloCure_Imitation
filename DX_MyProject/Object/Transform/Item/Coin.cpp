#include "framework.h"

Coin::Coin()
	:Item()
	, speed(100.0f)
	, idleSPD(10.0f)
	, changeTime(0.5f)
	, nowTime(0.5f)
	, isUp(false)
	,coinAmount(0)
{
	wstring file = L"Textures/Item/PC Computer - HoloCure - Save the Fans - Pickups_rm_bg.png";
	Texture* t = Texture::Add(file);

	vector<Frame*> frames;

	// coin clip
	Vector2 initPos(4, 300);
	for (int i = 0; i < 8; i++)
	{
		frames.push_back(new Frame(file, initPos.x+17*i, 300.0f, 15.0f, 15.0f));
	}
	clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP, 1.0f / 6.0f));
	frames.clear();

	// collider
	colliders.push_back(new RectCollider(Vector2(15.0f, 15.0f) * 2.0f));
	collider = colliders[0];
	collider->pos = pos;

	clip_idx = 0;
	scale = clips[clip_idx]->GetFrameSize() * collider->Size() / clips[clip_idx]->GetFrameOriginSize();

	id = ITEM_ID::COIN;
	type = ITEM_TYPE::COIN;

	is_active = false;
	collider->SetActive(false);
}

Coin::~Coin()
{
	for (auto c : colliders)
	{
		if (c != nullptr)
			delete c;
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
			pos -= Vector2(0, 1.f) * idleSPD * DELTA;
		else
			pos += Vector2(0, 1.0f) * idleSPD * DELTA;

		if (nowTime >= changeTime)
		{
			isUp = !isUp;
			nowTime -= changeTime;
		}
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

	scale = clips[clip_idx]->GetFrameSize() * collider->Size() / clips[clip_idx]->GetFrameOriginSize();
	clips[clip_idx]->Update();

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

void Coin::Respawn()
{
	state = ITEM_STATE::IDLE;

	WorldUpdate();
	collider->pos = pos;
	collider->WorldUpdate();

	scale = clips[clip_idx]->GetFrameSize() * collider->Size() /
		clips[clip_idx]->GetFrameOriginSize();

	is_active = true;
	collider->SetActive(true);
}