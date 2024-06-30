#include "framework.h"

RewardBoxAnim::RewardBoxAnim()
{
	wstring file = L"Textures/Item/PC Computer - HoloCure - Save the Fans - Holozon Box.png";
	vector<Frame*> frames;
	// Fall clip
	for (int i = 0; i < 4; i++)
	{
		frames.push_back(new Frame(file, 4.0f, 487.0f + 362.0f * i, 640.0f, 360.0f));
	}
	clips.push_back(new Clip(frames, Clip::CLIP_TYPE::END, 1.0f / 8.0f));
	frames.clear();
	// Closed clip
	frames.push_back(new Frame(file, 4.0f, 328.0f, 186.0f, 131.0f));
	clips.push_back(new Clip(frames, Clip::CLIP_TYPE::END, 1.0f));
	frames.clear();
	// Bouncing clip
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			frames.push_back(new Frame(file, 652.0f + 188.0f * j, 52.0f + 133.0f * i, 186.0f, 131.0f));
		}
	}
	clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP, 1.0f / 8.0f));
	frames.clear();
	// Opening clip
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			frames.push_back(new Frame(file, 652.0f + 242.0f * j, 608.0f + 250.0f * i, 240.0f, 248.0f));
		}
	}
	frames.push_back(new Frame(file, 652.0f, 1608.0f, 240.0f, 248.0f));
	clips.push_back(new Clip(frames, Clip::CLIP_TYPE::END, 1.0f / 8.0f));
	frames.clear();
	// Open clip
	frames.push_back(new Frame(file, 4.0f, 52.0f, 240.0f, 248.0f));
	clips.push_back(new Clip(frames, Clip::CLIP_TYPE::END, 1.0f));
	frames.clear();

	id = UI_ID::IMAGE;
	type = UI_TYPE::IMAGE;
	state = UI_STATE::IDLE;
	boxState = BOX_STATE::FALL;
	SetActive(false);
}

RewardBoxAnim::~RewardBoxAnim()
{
}

void RewardBoxAnim::Update()
{
	if (!is_active)return;

	switch (boxState)
	{
	case RewardBoxAnim::BOX_STATE::FALL:
		ui_size = Vector2(640.0f, 360.0f);
		break;
	case RewardBoxAnim::BOX_STATE::CLOSED:
		ui_size = Vector2(186.0f, 131.0f);
		break;
	case RewardBoxAnim::BOX_STATE::BOUNCING:
		ui_size = Vector2(186.0f, 131.0f);
		break;
	case RewardBoxAnim::BOX_STATE::OPENING:
		ui_size = Vector2(240.0f, 248.0f);
		break;
	case RewardBoxAnim::BOX_STATE::OPEN:
		ui_size = Vector2(240.0f, 248.0f);
		break;
	default:
		break;
	}
	clips[clip_idx]->Update();
	scale = clips[clip_idx]->GetFrameSize() * ui_size / clips[clip_idx]->GetFrameOriginSize() * ui_scale;

	if (target != nullptr)
		pos = target->pos + offset;

	WorldUpdate();
	for (auto c : child_list)
		c->Update();
}

void RewardBoxAnim::Render()
{
	if (!is_active)return;
	
	VS->Set();
	PS->Set();

	WB->SetVS(0);
	CB->SetPS(0);

	clips[clip_idx]->Render();
	for (auto c : child_list)
		c->Update();
}

void RewardBoxAnim::PostRender()
{
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
		clip_idx = 0;
		break;
	case RewardBoxAnim::BOX_STATE::CLOSED:
		clip_idx = 1;
		break;
	case RewardBoxAnim::BOX_STATE::BOUNCING:
		clip_idx = 2;
		break;
	case RewardBoxAnim::BOX_STATE::OPENING:
		clip_idx = 3;
		break;
	case RewardBoxAnim::BOX_STATE::OPEN:
		clip_idx = 4;
		break;
	default:
		break;
	}
	// 처음부터 다시 재생하도록 지정
	clips[clip_idx]->Play();
}

void RewardBoxAnim::SetID(UI::UI_ID id)
{
	this->id = id;
}
