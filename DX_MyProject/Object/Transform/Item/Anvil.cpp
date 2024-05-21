#include "framework.h"

Anvil::Anvil(Vector2 pos, Vector2 size)
	:Item()
	,coolTime(0.0f)
{
	wstring file = L"Textures/Item/PC Computer - HoloCure - Save the Fans - Pickups_rm_bg.png";
	Texture* t = Texture::Add(file);

	vector<Frame*> frames;
	// anvil clip
	frames.push_back(new Frame(file, 81.0f, 179.0f, 41.0f, 24.0f));
	clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP, 1.0f / 1.0f));
	frames.clear();
	// golden anvil clip
	frames.push_back(new Frame(file, 147.0f, 179.0f, 41.0f, 24.0f));
	clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP, 1.0f / 1.0f));
	frames.clear();

	collider = new RectCollider(Vector2(41.0f, 24.0f) * 1.5f);
	id = ITEM_ID::ANVIL;
	type = ITEM_TYPE::ANVIL;

	light = new AnvilLight(pos);
	
	CB->data.colour = Float4(1.0f, 1.0f, 1.0f, 0.95f);
	is_active = false;
	collider->SetActive(false);
}

Anvil::~Anvil()
{
	delete collider;
	delete light;
}

void Anvil::Update()
{
	if (!is_active)return;

	switch (state)
	{
	case Item::ITEM_STATE::IDLE:
		if (coolTime > 0.0f)
		{
			collider->SetActive(false);
			coolTime -= DELTA;
		}
		else
		{
			collider->SetActive(true);
		}
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

void Anvil::Render()
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

void Anvil::PostRender()
{
	if (!is_active)return;
}

void Anvil::Respawn()
{
	state = ITEM_STATE::IDLE;

	WorldUpdate();
	collider->pos = pos;
	collider->WorldUpdate();
	light->SetPos(pos);
	
	scale = clips[clip_idx]->GetFrameSize() * collider->Size() /
		clips[clip_idx]->GetFrameOriginSize();
	coolTime = 0.0f;

	is_active = true;
	collider->SetActive(true);
	light->SetActive(true);
}

void Anvil::SetStatus(Item::ITEM_ID id, int value)
{
	switch (id)
	{
	case Item::ITEM_ID::ANVIL:
	{
		SetUseCnt(value);
		clip_idx = 0;
	}
		break;
	case Item::ITEM_ID::GOLDEN_ANVIL:
	{
		useCnt = 1;
		clip_idx = 1;
	}
		break;
	default:
		break;
	}
}

void Anvil::SetState(ITEM_STATE state)
{
	this->state = state;
	switch (state)
	{
	case Item::ITEM_STATE::IDLE:
	{
		coolTime = 2.0f;
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
		useCnt--;
		if (useCnt > 0)
		{
			SetState(ITEM_STATE::IDLE);
		}
	}
		break;
	default:
		break;
	}
}

void Anvil::SetPos(Vector2 pos)
{
	this->pos = pos; 
	collider->pos = pos;
}

void Anvil::SetAmount(int value)
{
	useCnt = value;
}

int Anvil::GetAmount()
{
	return useCnt;
}

