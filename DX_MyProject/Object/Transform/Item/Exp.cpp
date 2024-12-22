#include "framework.h"

vector<vector<shared_ptr<const Frame>>> Exp::expFrames;
int Exp::expUseCnt = 0;

Exp::Exp()
	:Item()
	, speed(100.0f)
	,idleSPD(10.0f)
	,changeTime(0.5f)
	,nowTime(0.5f)
	,isUp(false)
{
	if (expFrames.empty())
	{
		InitFrame();
	}

	// magnetCollider
	colliders.emplace_back(new RectCollider(Vector2(23.0f, 24.0f) * 1.5f));
	// exp collider
	colliders.emplace_back(new RectCollider(Vector2(12.0f,13.0f)*1.5f));
	collider = colliders[0];
	collider->pos = pos;

	scale = clips[expLevel]->GetFrameSize() * collider->Size() / clips[expLevel]->GetFrameOriginSize();

	id = ITEM_ID::EXP;
	type = ITEM_TYPE::EXP;

	is_active = false;
	collider->SetActive(false);

	SetExp(1);
	++expUseCnt;
}

Exp::~Exp()
{
	for (auto c : colliders)
	{
		if (c != nullptr)
			delete c;
	}

	if ((--expUseCnt) == 0)
	{
		ClearFrame();
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
				moveDir = Vector2(0.0f, -1.0f);
			else
				moveDir = Vector2(0.0f, 1.0f);

			if (nowTime >= changeTime)
			{
				isUp = !isUp;
				nowTime -= changeTime;
			}

			if (addtionalDir.GetLength() > 0.1f)
				moveDir = (moveDir + addtionalDir).Normalized();
			pos += moveDir * idleSPD * DELTA;
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
			vector<Item*> itemList = ItemSpawner::Get()->GetItemList();
			for (auto i : itemList)
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

	scale = clips[expLevel]->GetFrameSize() * collider->Size() / clips[expLevel]->GetFrameOriginSize();
	clips[expLevel]->Update();

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

	clips[expLevel]->Render();
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

void Exp::SetAmount(int inAmount)
{
	SetExp(inAmount);
}

void Exp::InitFrame()
{
	if (!(expFrames.empty())) return;

	wstring file = L"Textures/Item/PC Computer - Homake_shared<const Frame>loCure - Save the Fans - EXP_rm_bg.png";
	
	// exp magnet
	{
		vector<shared_ptr<const Frame>> expMagnetFrames;
		expMagnetFrames.emplace_back(make_shared<const Frame>(file, 58.5f, 435.0f, 23.0f, 24.0f));
		expMagnetFrames.emplace_back(make_shared<const Frame>(file, 188.5f, 435.0f, 23.0f, 24.0f));
		expMagnetFrames.emplace_back(make_shared<const Frame>(file, 318.5f, 435.0f, 23.0f, 24.0f));
		expMagnetFrames.emplace_back(make_shared<const Frame>(file, 58.0f, 564.0f, 23.0f, 24.0f));
		expMagnetFrames.emplace_back(make_shared<const Frame>(file, 188.0f, 563.0f, 23.0f, 24.0f));
		expMagnetFrames.emplace_back(make_shared<const Frame>(file, 318.0f, 561.5f, 23.0f, 24.0f));
		expMagnetFrames.emplace_back(make_shared<const Frame>(file, 58.0f, 692.0f, 23.0f, 24.0f));
		expMagnetFrames.emplace_back(make_shared<const Frame>(file, 188.0f, 692.0f, 23.0f, 24.0f));
		expMagnetFrames.emplace_back(make_shared<const Frame>(file, 318.0f, 692.0f, 23.0f, 24.0f));
		expMagnetFrames.emplace_back(make_shared<const Frame>(file, 58.0f, 823.0f, 23.0f, 24.0f));
		expMagnetFrames.emplace_back(make_shared<const Frame>(file, 188.0f, 824.0f, 23.0f, 24.0f));
		expMagnetFrames.emplace_back(make_shared<const Frame>(file, 318.0f, 825.0f, 23.0f, 24.0f));
		expFrames.push_back(expMagnetFrames);
	}
	// exp
	{
		vector<shared_ptr<const Frame>> normalExpFrames;
		// exp 1~10
		normalExpFrames.emplace_back(make_shared<const Frame>(file, 63.0f, 157.0f, 12.0f, 13.0f));
		// exp 11~19
		normalExpFrames.emplace_back(make_shared<const Frame>(file, 193.0f, 157.0f, 12.0f, 13.0f));
		// exp 20~49
		normalExpFrames.emplace_back(make_shared<const Frame>(file, 323.0f, 157.0f, 12.0f, 13.0f));
		// exp 50~99
		normalExpFrames.emplace_back(make_shared<const Frame>(file, 63.0f, 287.0f, 12.0f, 13.0f));
		// exp 100~199
		normalExpFrames.emplace_back(make_shared<const Frame>(file, 193.0f, 287.0f, 12.0f, 13.0f));
		// exp 200+
		normalExpFrames.emplace_back(make_shared<const Frame>(file, 323.0f, 287.0f, 12.0f, 13.0f));
		expFrames.push_back(normalExpFrames);
	}
}

void Exp::ClearFrame()
{
	if (expFrames.empty()) return;

	expFrames.clear();
}

void Exp::SetExp(int expAmount)
{
	exp = expAmount;

	if (exp == 0)
		expLevel = 0;
	else if (exp <= 10)
		expLevel = 1;
	else if (exp < 20)
		expLevel = 2;
	else if (exp < 50)
		expLevel = 3;
	else if (exp < 100)
		expLevel = 4;
	else if (exp < 200)
		expLevel = 5;
	else
		expLevel = 6;

	SetFrame();
}

void Exp::SetFrame()
{
	if (expLevel != 0)
	{
		frame = expFrames[1][expLevel - 1];
		if (!(clips.empty()))
		{
			clips.clear();
		}
	}
	else if (frame)
	{
		clips.emplace_back(make_shared<Clip>(expFrames[0], Clip::CLIP_TYPE::LOOP, 1.0f / 12.0f));
		frame.reset();
	}
}

void Exp::Respawn()
{
	state = ITEM_STATE::IDLE; 
	
	WorldUpdate();
	collider->pos = pos;
	collider->WorldUpdate();

	if (expLevel == 0)
	{
		scale = clips[clipIdx]->GetFrameSize() * collider->Size() /
			clips[clipIdx]->GetFrameOriginSize();
	}
	else
	{
		scale = frame->GetFrameSize() * collider->Size() /
			frame->GetFrameOriginSize();
	}

	is_active = true;
	collider->SetActive(true);
}