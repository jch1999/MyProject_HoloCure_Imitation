#include "framework.h"

RewardBox::RewardBox(Vector2 pos, Vector2 size)
	:Item()
	,reward_coin(0)
{
	wstring file = L"Textures/Item/PC Computer - HoloCure - Save the Fans - Pickups_rm_bg.png";
	Texture* t = Texture::Add(file);

	vector<Frame*> frames;
	// RewardBox clip
	frames.push_back(new Frame(file, 20.0f, 184.0f, 33.0f, 19.0f));
	clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP, 1.0f / 1.0f));
	frames.clear();

	collider = new RectCollider(Vector2(33.0f, 19.0f) * 1.5f);
	id = ITEM_ID::REWORD_BOX;
	type = ITEM_TYPE::REWARD_BOX;

	light = new ItemLight(pos);
	light->SetOffset(Vector2(-5.0f, -44.0f));

	light->SetActive(false);
	is_active = false;
	collider->SetActive(false);
}

RewardBox::~RewardBox()
{
	delete collider;
	delete light;
}

void RewardBox::Update()
{
	if (!is_active)return;

	switch (state)
	{
	case Item::ITEM_STATE::IDLE:
		break;
	case Item::ITEM_STATE::ACTIVE:
		SetState(ITEM_STATE::USED);
		break;
	case Item::ITEM_STATE::USED:
		is_active = false;
		collider->SetActive(false);
		break;
	default:
		break;
	}
	light->Update();
	clips[clip_idx]->Update();
	scale = clips[clip_idx]->GetFrameSize() * collider->Size() / clips[clip_idx]->GetFrameOriginSize();
	WorldUpdate();
	collider->pos = pos;
	collider->WorldUpdate();
}

void RewardBox::Render()
{
	if (!is_active)return;

	VS->Set();
	PS->Set();

	WB->SetVS(0);
	CB->SetPS(0);

	clips[clip_idx]->Render();
	light->Render();
	collider->Render();
}

void RewardBox::PostRender()
{
	if (!is_active)return;
}

void RewardBox::Respawn()
{
	state = ITEM_STATE::IDLE;

	WorldUpdate();
	collider->pos = pos;
	collider->WorldUpdate();
	light->SetPos(pos);

	scale = clips[clip_idx]->GetFrameSize() * collider->Size() /
		clips[clip_idx]->GetFrameOriginSize();

	is_active = true;
	collider->SetActive(true);
	light->SetActive(true);
}

void RewardBox::SetStatus(Item::ITEM_ID id, int value)
{
	this->id = id;
	reward_coin = value;
}

void RewardBox::SetState(ITEM_STATE state)
{
	this->state = state;
	switch (state)
	{
	case Item::ITEM_STATE::IDLE:
	{
	}
	break;
	case Item::ITEM_STATE::ACTIVE:
	{
		isPause = true;
		collider->SetActive(false);
	}
	break;
	case Item::ITEM_STATE::USED:
	{
	}
	break;
	default:
		break;
	}
}

void RewardBox::SetPos(Vector2 pos)
{
	this->pos = pos;
	collider->pos = pos;
	light->SetPos(pos);
}

void RewardBox::SetAmount(int value)
{
	reward_coin = value;
}

int RewardBox::GetAmount()
{
	return reward_coin;
}

