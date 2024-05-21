#include "framework.h"

Exp::Exp()
	:Item()
	, speed(100.0f)
	,idleSPD(10.0f)
	,changeTime(0.5f)
	,nowTime(0.5f)
	,isUp(false)
{
	wstring file = L"Textures/Item/PC Computer - HoloCure - Save the Fans - EXP_rm_bg.png";
	Texture* t = Texture::Add(file);

	SetExp(1);

	vector<Frame*> frames;

	// exp magnet
	frames.push_back(new Frame(file, 58.5f, 435.0f, 23.0f, 24.0f));
	frames.push_back(new Frame(file, 188.5f, 435.0f, 23.0f, 24.0f));
	frames.push_back(new Frame(file, 318.5f, 435.0f, 23.0f, 24.0f));
	frames.push_back(new Frame(file, 58.0f, 564.0f, 23.0f, 24.0f));
	frames.push_back(new Frame(file, 188.0f, 563.0f, 23.0f, 24.0f));
	frames.push_back(new Frame(file, 318.0f, 561.5f, 23.0f, 24.0f));
	frames.push_back(new Frame(file, 58.0f, 692.0f, 23.0f, 24.0f));
	frames.push_back(new Frame(file, 188.0f, 692.0f, 23.0f, 24.0f));
	frames.push_back(new Frame(file, 318.0f, 692.0f, 23.0f, 24.0f));
	frames.push_back(new Frame(file, 58.0f, 823.0f, 23.0f, 24.0f));
	frames.push_back(new Frame(file, 188.0f, 824.0f, 23.0f, 24.0f));
	frames.push_back(new Frame(file, 318.0f, 825.0f, 23.0f, 24.0f));

	clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP, 1.0f / 12.0f));
	frames.clear();

	// exp 1~10
	frames.push_back(new Frame(file, 63.0f, 157.0f, 12.0f, 13.0f));
	clips.push_back(new Clip(frames, Clip::CLIP_TYPE::END, 1.0f));
	frames.clear();

	// exp 11~19
	frames.push_back(new Frame(file, 193.0f, 157.0f, 12.0f, 13.0f));
	clips.push_back(new Clip(frames, Clip::CLIP_TYPE::END, 1.0f));
	frames.clear();

	// exp 20~49
	frames.push_back(new Frame(file, 323.0f, 157.0f, 12.0f, 13.0f));
	clips.push_back(new Clip(frames, Clip::CLIP_TYPE::END, 1.0f));
	frames.clear();

	// exp 50~99
	frames.push_back(new Frame(file, 63.0f, 287.0f, 12.0f, 13.0f));
	clips.push_back(new Clip(frames, Clip::CLIP_TYPE::END, 1.0f));
	frames.clear();

	// exp 100~199
	frames.push_back(new Frame(file, 193.0f, 287.0f, 12.0f, 13.0f));
	clips.push_back(new Clip(frames, Clip::CLIP_TYPE::END, 1.0f));
	frames.clear();

	// exp 200+
	frames.push_back(new Frame(file, 323.0f, 287.0f, 12.0f, 13.0f));
	clips.push_back(new Clip(frames, Clip::CLIP_TYPE::END, 1.0f));
	frames.clear();


	// magnetCollider
	colliders.push_back(new RectCollider(Vector2(23.0f, 24.0f) * 1.5f));
	// exp collider
	colliders.push_back(new RectCollider(Vector2(12.0f,13.0f)*1.5f));
	collider = colliders[0];
	collider->pos = pos;

	scale = clips[exp_level]->GetFrameSize() * collider->Size() / clips[exp_level]->GetFrameOriginSize();

	id = ITEM_ID::EXP;
	type = ITEM_TYPE::EXP;

	is_active = false;
	collider->SetActive(false);
}

Exp::~Exp()
{
	for (auto c : colliders)
	{
		if (c != nullptr)
			delete c;
	}
}

void Exp::Update()
{
	if (!is_active)return;
	switch (state)
	{
	case Item::ITEM_STATE::IDLE:
	{
		if (id == ITEM_ID::EXP)
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
	}
		break;
	case Item::ITEM_STATE::ACTIVE:
	{
		pos = LERP(pos, target->pos, speed / 30.0f * DELTA);
	}
		break;
	case Item::ITEM_STATE::USED:
	{
		if(id==ITEM_ID::EXP)
			target->GetExp(exp);
		else if (id == ITEM_ID::EXP_MAGNET)
		{
			vector<Item*> item_list = ItemSpawner::Get()->GetItemList();
			for (auto i : item_list)
			{
				if (!i->is_active)continue;
				if (i->id == ITEM_ID::EXP || i->id == ITEM_ID::COIN)
					i->SetState(ITEM_STATE::ACTIVE);
			}
		}
		is_active = false;
		collider->SetActive(false);
	}
		break;
	default:
		break;
	}

	scale = clips[exp_level]->GetFrameSize() * collider->Size() / clips[exp_level]->GetFrameOriginSize();
	clips[exp_level]->Update();

	WorldUpdate();
	
	collider->pos = pos;
	collider->WorldUpdate();
}

void Exp::Render()
{
	if (!is_active)return;
	
	VS->Set();
	PS->Set();

	WB->SetVS(0);
	CB->SetPS(0);

	clips[exp_level]->Render();
	collider->Render();
}

void Exp::PostRender()
{
	if (!is_active)return;
}

void Exp::SetStatus(Item::ITEM_ID id, int value)
{
	SetExp(value);
	this->id = id;

	switch (id)
	{
	case Item::ITEM_ID::EXP:
	{
		collider->SetActive(false);
		collider = colliders[1];
	}
	break;
	case Item::ITEM_ID::EXP_MAGNET:
	{
		collider->SetActive(false);
		collider = colliders[0];
	}
	break;
	default:
		break;
	}
}

void Exp::SetPos(Vector2 pos)
{
	this->pos = pos;
	collider->pos = pos;
}

void Exp::SetExp(int expAmount)
{
	exp = expAmount;

	if (exp == 0)
		exp_level = 0;
	else if (exp <= 10)
		exp_level = 1;
	else if (exp < 20)
		exp_level = 2;
	else if (exp < 50)
		exp_level = 3;
	else if (exp < 100)
		exp_level = 4;
	else if (exp < 200)
		exp_level = 5;
	else
		exp_level = 6;
}

void Exp::Respawn()
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