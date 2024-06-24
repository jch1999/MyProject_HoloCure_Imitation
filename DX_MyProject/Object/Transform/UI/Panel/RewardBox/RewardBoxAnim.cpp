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
	clips.push_back(new Clip(frames, Clip::CLIP_TYPE::END, 1.0f / 4.0f));
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

	ui_size = clips[clip_idx]->GetFrameSize();
	scale = clips[clip_idx]->GetFrameSize() * ui_size / clips[clip_idx]->GetFrameOriginSize() * ui_scale;
	for (auto c : child_list)
		c->Update();
}

void RewardBoxAnim::Render()
{
	if (!is_active)return;

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

void RewardBoxAnim::SetID(UI::UI_ID id)
{
}
