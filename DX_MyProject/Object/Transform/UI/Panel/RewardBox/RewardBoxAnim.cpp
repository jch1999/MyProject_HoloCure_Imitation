#include "framework.h"

vector<vector<shared_ptr<const Frame>>>& RewardBoxAnim::GetRewardBoxAnimFrames()
{
	static vector<vector<shared_ptr<const Frame>>> rewardBoxAnimFrames;
	return rewardBoxAnimFrames;
}

int& RewardBoxAnim::GetRewardBoxAnimUseCnt()
{
	static int rewardBoxAnimUseCnt = 0;
	return rewardBoxAnimUseCnt;
}

RewardBoxAnim::RewardBoxAnim()
	:UI()
{
	if (GetRewardBoxAnimFrames().empty())
	{
		InitFrame();
	}

	clips.emplace_back(make_shared<Clip>(GetRewardBoxAnimFrames()[0], Clip::CLIP_TYPE::END, 1.0f / 8.0f));
	clips.emplace_back(make_shared<Clip>(GetRewardBoxAnimFrames()[1], Clip::CLIP_TYPE::END, 1.0f));
	clips.emplace_back(make_shared<Clip>(GetRewardBoxAnimFrames()[2], Clip::CLIP_TYPE::LOOP, 1.0f / 8.0f));
	clips.emplace_back(make_shared<Clip>(GetRewardBoxAnimFrames()[3], Clip::CLIP_TYPE::END, 1.0f / 8.0f));
	clips.emplace_back(make_shared<Clip>(GetRewardBoxAnimFrames()[4], Clip::CLIP_TYPE::END, 1.0f));
	
	id = UI_ID::IMAGE;
	type = UI_TYPE::IMAGE;
	state = UI_STATE::IDLE;
	boxState = BOX_STATE::FALL;
	SetActive(false);

	++GetRewardBoxAnimUseCnt();
}

RewardBoxAnim::~RewardBoxAnim()
{
	if ((--GetRewardBoxAnimUseCnt()) == 0)
	{
		ClearFrame();
	}
}

void RewardBoxAnim::Update()
{
	if (!is_active)return;

	switch (boxState)
	{
	case RewardBoxAnim::BOX_STATE::FALL:
		uiSize = Vector2(640.0f, 360.0f);
		break;
	case RewardBoxAnim::BOX_STATE::CLOSED:
		uiSize = Vector2(186.0f, 131.0f);
		break;
	case RewardBoxAnim::BOX_STATE::BOUNCING:
		uiSize = Vector2(186.0f, 131.0f);
		break;
	case RewardBoxAnim::BOX_STATE::OPENING:
		uiSize = Vector2(240.0f, 248.0f);
		break;
	case RewardBoxAnim::BOX_STATE::OPEN:
		uiSize = Vector2(240.0f, 248.0f);
		break;
	default:
		break;
	}
	clips[clipIdx]->Update();
	scale = clips[clipIdx]->GetFrameSize() * uiSize / clips[clipIdx]->GetFrameOriginSize() * uiScale;

	if (target != nullptr)
		pos = target->pos + offset;

	WorldUpdate();
	for (auto c : childList)
		c->Update();
}

void RewardBoxAnim::Render()
{
	if (!is_active)return;
	
	VS->Set();
	PS->Set();

	WB->SetVS(0);
	CB->SetPS(0);

	clips[clipIdx]->Render();
	for (auto c : childList)
		c->Update();
}

void RewardBoxAnim::InitFrame()
{
	auto& rewardBoxAnimFraems = GetRewardBoxAnimFrames();
	if (!(rewardBoxAnimFraems.empty())) return;

	wstring file = L"Textures/Item/PC Computer - HoloCure - Save the Fans - Holozon Box.png";

	// Fall clip
	{
		vector<shared_ptr<const Frame>> fallFrames;
		for (int i = 0; i < 4; i++)
		{
			fallFrames.emplace_back(make_shared<const Frame>(file, 4.0f, 487.0f + 362.0f * i, 640.0f, 360.0f));
		}
		rewardBoxAnimFraems.push_back(fallFrames);
	}
	// Closed clip
	{
		vector<shared_ptr<const Frame>> closedFrames;
		closedFrames.emplace_back(make_shared<const Frame>(file, 4.0f, 328.0f, 186.0f, 131.0f));
		rewardBoxAnimFraems.push_back(closedFrames);
	}
	// Bouncing clip
	{
		vector<shared_ptr<const Frame>> bouncingFrames;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				bouncingFrames.emplace_back(make_shared<const Frame>(file, 652.0f + 188.0f * j, 52.0f + 133.0f * i, 186.0f, 131.0f));
			}
		}
		rewardBoxAnimFraems.push_back(bouncingFrames);
	}
	// Opening clip
	{
		vector<shared_ptr<const Frame>> openingFrames;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				openingFrames.emplace_back(make_shared<const Frame>(file, 652.0f + 242.0f * j, 608.0f + 250.0f * i, 240.0f, 248.0f));
			}
		}
		openingFrames.emplace_back(make_shared<const Frame>(file, 652.0f, 1608.0f, 240.0f, 248.0f));
		rewardBoxAnimFraems.push_back(openingFrames);
	}
	// Open clip
	{
		vector<shared_ptr<const Frame>> openFrames;
		openFrames.emplace_back(make_shared<const Frame>(file, 4.0f, 52.0f, 240.0f, 248.0f));
		rewardBoxAnimFraems.push_back(openFrames);
	}
}

void RewardBoxAnim::ClearFrame()
{
	GetRewardBoxAnimFrames().clear();
}

void RewardBoxAnim::SetState(UI::UI_STATE state)
{
}

void RewardBoxAnim::SetAnimState(BOX_STATE bState)
{
	boxState = bState;
	switch (boxState)
	{
	case RewardBoxAnim::BOX_STATE::FALL:
		clipIdx = 0;
		break;
	case RewardBoxAnim::BOX_STATE::CLOSED:
		clipIdx = 1;
		break;
	case RewardBoxAnim::BOX_STATE::BOUNCING:
		clipIdx = 2;
		break;
	case RewardBoxAnim::BOX_STATE::OPENING:
		clipIdx = 3;
		break;
	case RewardBoxAnim::BOX_STATE::OPEN:
		clipIdx = 4;
		break;
	default:
		break;
	}
	// 처음부터 다시 재생하도록 지정
	clips[clipIdx]->Play();
}

void RewardBoxAnim::SetID(UI::UI_ID id)
{
	this->id = id;
}
