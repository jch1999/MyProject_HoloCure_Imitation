#include "framework.h"

PlayerIcon::PlayerIcon()
{
	vector<wstring> files =
	{
		// PlayerIcon & Defulat Weapon Skill Icon
		L"Textures/Player/PC Computer - HoloCure - Save the Fans - Amelia Watson_rm_bg.png",
		L"Textures/Player/PC Computer - HoloCure - Save the Fans - Takanashi Kiara_rm_bg.png",
		L"Textures/Player/PC Computer - HoloCure - Save the Fans - Hakos Baelz_rm_bg.png",
	};
	vector<Frame*> frames;

	// Player Icon
	// Watson
	frames.push_back(new Frame(files[0], 10, 2363, 43, 38));
	clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP, 1));
	frames.clear();
	// Kiara
	frames.push_back(new Frame(files[1], 10, 3953, 43, 38));
	clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP, 1));
	frames.clear();
	// Baelz
	frames.push_back(new Frame(files[2], 10, 802, 43, 38));
	clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP, 1));
	frames.clear();

	// Player Full Icon
	// Watson
	frames.push_back(new Frame(files[0], 7, 2419, 73, 105));
	clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP, 1));
	frames.clear();
	// Kiara
	frames.push_back(new Frame(files[1], 7, 4008, 63, 115));
	clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP, 1));
	frames.clear();
	// Baelz
	frames.push_back(new Frame(files[2], 7, 858, 73, 112));
	clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP, 1));
	frames.clear();

	id = UI::UI_ID::PLAYER_ICON;
	type = UI::UI_TYPE::ICON;
	state = UI::UI_STATE::IDLE;
	ui_size = Vector2(43.0f, 38.0f);
	ui_scale = Vector2(1, 1);
	additional_scale = Vector2(1, 1);
	offset = Vector2(0, 0);
	is_active = false;
}

PlayerIcon::~PlayerIcon()
{
}

void PlayerIcon::Update()
{
	if (!is_active)return;

	scale = clips[clip_idx]->GetFrameSize() * ui_size / clips[clip_idx]->GetFrameOriginSize() * ui_scale * additional_scale;
	clips[clip_idx]->Update();

	pos = target->pos + offset;
	WorldUpdate();
}

void PlayerIcon::Render()
{
	if (!is_active)return;
	VS->Set();
	PS->Set();

	WB->SetVS(0);
	CB->SetPS(0);

	clips[clip_idx]->Render();
}

void PlayerIcon::PostRender()
{
}

void PlayerIcon::SetState(UI::UI_STATE state)
{
	this->state = state;
}

void PlayerIcon::SetID(UI::UI_ID id)
{
	this->id = id;
	switch (id)
	{
	case UI::UI_ID::PLAYER_ICON:
	{
		// PlayerIconFrame의 경우 생성시기가 UIManager에 Player가 대입되는 시기보다 빠름
		// 따라서 다른 곳에서 player정보를 가져와야 함
		Player::PLAYER_ID p_id = EnemySpawner::Get()->GetPlayer()->player_id;
		switch (p_id)
		{
		case Player::PLAYER_ID::WATSON:
		{
			clip_idx = 0;
		}
		break;
		case Player::PLAYER_ID::KIARA:
		{
			clip_idx = 1;
		}
		break;
		case Player::PLAYER_ID::BAELZ:
		{
			clip_idx = 2;
		}
		break;
		default:
			break;
		}
		CB->data.colour = Float4(1.0f, 1.0f, 1.0f, 1.0f);
		SetSize(Vector2(43.0f, 38.0f));
	}
		break;
	case UI::UI_ID::PLAYER_FULL_ICON:
	{
		// PlayerIconFrame의 경우 생성시기가 UIManager에 Player가 대입되는 시기보다 빠름
		// 따라서 다른 곳에서 player정보를 가져와야 함
		Player::PLAYER_ID p_id = EnemySpawner::Get()->GetPlayer()->player_id;
		switch (p_id)
		{
		case Player::PLAYER_ID::WATSON:
		{
			clip_idx = 3;
			SetSize(Vector2(73.0f, 105.0f));
		}
		break;
		case Player::PLAYER_ID::KIARA:
		{
			clip_idx = 4;
			SetSize(Vector2(63.0f, 115.0f));
		}
		break;
		case Player::PLAYER_ID::BAELZ:
		{
			clip_idx = 5;
			SetSize(Vector2(73.0f, 112.0f));
		}
		break;
		default:
			break;
		}
		CB->data.colour = Float4(0.95f, 0.95f, 0.95f, 0.85f);
	}
		break;
	default:
		break;
	}
}
