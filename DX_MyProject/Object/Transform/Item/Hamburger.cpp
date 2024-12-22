#include "framework.h"

vector<shared_ptr<const Frame>> Hambureger::hambugerFrames;
int Hambureger::hambugerUseCnt = 0;

Hambureger::Hambureger()
	:Item()
	, speed(100.0f)
	,healAmount(0.0f)
{
	if (hambugerFrames.empty())
	{
		InitFrame();
	}

	clips.emplace_back(make_shared<Clip>(hambugerFrames, Clip::CLIP_TYPE::LOOP, 1.0f / 6.0f));

	collider = new RectCollider(Vector2(17.0f, 18.0f) * 1.5f);

	id = ITEM_ID::HAMBURGER;
	type = ITEM_TYPE::FOOD;

	is_active = false;
	collider->SetActive(false);

	++hambugerUseCnt;
}

Hambureger::~Hambureger()
{
	delete collider;

	if ((--hambugerUseCnt) == 0)
	{
		ClearFrame();
	}
}

void Hambureger::Update()
{
	if (!is_active)return;

	if (target != nullptr)
		SetAmount(target->GetMaxHP() * 0.2f);

	switch (state)
	{
	case Item::ITEM_STATE::IDLE:
	{
		
	}
	break;
	case Item::ITEM_STATE::ACTIVE:
	{
		pos = LERP(pos, target->pos, speed / 30.0f * DELTA);
	}
	break;
	case Item::ITEM_STATE::USED:
	{
		// 추가회복량 계산후 대입

		target->ChangeHP(healAmount);
		
		is_active = false;
		collider->SetActive(false);
	}
	break;
	default:
		break;
	}

	scale = clips[0]->GetFrameSize() * collider->Size() / clips[0]->GetFrameOriginSize();
	clips[0]->Update();

	WorldUpdate();

	collider->pos = pos;
	collider->WorldUpdate();
}

void Hambureger::Render()
{
	if (!is_active)return;

	VS->Set();
	PS->Set();

	WB->SetVS(0);
	CB->SetPS(0);

	clips[0]->Render();
	collider->Render();
}

void Hambureger::PostRender()
{
	ImGui::Text("HealAmount : %f", healAmount);
}

void Hambureger::Respawn()
{
	state = ITEM_STATE::IDLE;

	scale = clips[clipIdx]->GetFrameSize() * collider->Size() /
		clips[clipIdx]->GetFrameOriginSize();

	WorldUpdate();
	collider->pos = pos;
	collider->WorldUpdate();

	is_active = true;
	collider->SetActive(true);
}

void Hambureger::InitFrame()
{
	if (!(hambugerFrames.empty())) return;

	wstring file = L"Textures/Item/PC Computer - HoloCure - Save the Fans - Pickups_rm_bg.png";

	Vector2 initPos(12.0f, 355.0f);
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			hambugerFrames.emplace_back(make_shared<const Frame>(file, initPos.x + j * 34.0f, initPos.y + i * 32.0f, 17.0f, 18.0f));
		}
	}
}

void Hambureger::ClearFrame()
{
	if (hambugerFrames.empty()) return;

	hambugerFrames.clear();
}

void Hambureger::SetStatus(Item::ITEM_ID id, int value)
{
	this->id = id;
	healAmount = value;
}

void Hambureger::SetPos(Vector2 pos)
{
	this->pos = pos;
	collider->pos = pos;
}

void Hambureger::SetAmount(int inAmount)
{
	healAmount = inAmount;
}
