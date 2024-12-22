#include "framework.h"

shared_ptr<const Frame> RewardBox::rewardBoxFrame;
int RewardBox::rewardBoxUseCnt = 0;

RewardBox::RewardBox(Vector2 pos, Vector2 size)
	:Item()
	,reward_coin(0)
{
	if (!rewardBoxFrame)
	{
		InitFrame();
	}

	// RewardBox clip
	frame = rewardBoxFrame;

	collider = new RectCollider(Vector2(33.0f, 19.0f) * 1.5f);
	id = ITEM_ID::REWORD_BOX;
	type = ITEM_TYPE::REWARD_BOX;

	light = new ItemLight(pos);
	light->SetOffset(Vector2(-5.0f, -44.0f));

	light->SetActive(false);
	is_active = false;
	collider->SetActive(false);

	++rewardBoxUseCnt;
}

RewardBox::~RewardBox()
{
	delete collider;
	delete light;

	if ((--rewardBoxUseCnt) == 0)
	{
		ClearFrame();
	}
}

void RewardBox::Update()
{
	if (!is_active)return;

	switch (state)
	{
	case Item::ITEM_STATE::IDLE:
		break;
	case Item::ITEM_STATE::ACTIVE:
	{
		if (UIManager::Get()->rewardPanel->GetBox() != this)
		{
			SetState(ITEM_STATE::IDLE);
		}
	}
		break;
	case Item::ITEM_STATE::USED:
		is_active = false;
		collider->SetActive(false);
		break;
	default:
		break;
	}
	
	light->Update();

	scale = frame->GetFrameSize() * collider->Size() / frame->GetFrameOriginSize();
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

	frame->Render();
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

	scale = frame->GetFrameSize() * collider->Size() /
		frame->GetFrameOriginSize();

	is_active = true;
	collider->SetActive(true);
	light->SetActive(true);
}

void RewardBox::InitFrame()
{
	if (rewardBoxFrame) return;

	wstring file = L"Textures/Item/PC Computer - HoloCure - Save the Fans - Pickups_rm_bg.png";
	rewardBoxFrame=make_shared<const Frame>(file, 20.0f, 184.0f, 33.0f, 19.0f);
}

void RewardBox::ClearFrame()
{
	if (!rewardBoxFrame) return;

	rewardBoxFrame.reset();
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
		collider->SetActive(true);
	}
	break;
	case Item::ITEM_STATE::ACTIVE:
	{
		isPause = true;
		collider->SetActive(false); 
		UIManager::Get()->isReward = true;
		UIManager::Get()->rewardPanel->SetBox(this);
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

