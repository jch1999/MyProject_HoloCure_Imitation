#include "framework.h"

Icon::Icon()
{
	vector<wstring> files =
	{
		// PlayerIcon & Defulat Weapon Skill Icon
		L"Textures/Player/PC Computer - HoloCure - Save the Fans - Amelia Watson_rm_bg.png",
		L"Textures/Player/PC Computer - HoloCure - Save the Fans - Takanashi Kiara_rm_bg.png",
		L"Textures/Player/PC Computer - HoloCure - Save the Fans - Hakos Baelz_rm_bg.png",
		// SkillIcon
		L"Textures/Skill/PC Computer - HoloCure - Save the Fans - Weapons_rm_bg.png",
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

	// Default Weapon Icon
	// PistolShot
	// Normal
	frames.push_back(new Frame(files[1], 11, 1956, 18, 20));
	clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP, 1));
	frames.clear();
	// Awake
	frames.push_back(new Frame(files[1], 34, 1956, 24, 25));
	clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP, 1));
	frames.clear();
	// PhoenixSword
	// Normal
	frames.push_back(new Frame(files[1], 8, 3683, 22, 21));
	clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP, 1));
	frames.clear();
	// Awake
	frames.push_back(new Frame(files[1], 33, 3684, 25, 25));
	clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP, 1));
	frames.clear();
	// PlayDice
	// Normal
	frames.push_back(new Frame(files[1], 9, 703, 21, 20));
	clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP, 1));
	frames.clear();
	// Awake
	frames.push_back(new Frame(files[1], 33, 703, 25, 20));
	clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP, 1));
	frames.clear();

	// Weapon Skill Icon

	// Buff Skill Icon

	id = UI::UI_ID::PLAYER_ICON;
	type = UI::UI_TYPE::IMAGE;
	state = UI::UI_STATE::IDLE;
	ui_size = Vector2(43.0f, 38.0f);
	ui_scale = Vector2(1, 1);
	additional_scale = Vector2(1, 1);
	offset = Vector2(0, 0);
	is_active = false;
}

Icon::~Icon()
{
}

void Icon::Update()
{
	if (!is_active)return;

	scale = clips[clip_idx]->GetFrameSize() * ui_size / clips[clip_idx]->GetFrameOriginSize() * ui_scale;
	clips[clip_idx]->Update();

	pos = target->pos + offset - Vector2((1 - ui_scale.x) / 2.0f, 0) * ui_size;
	WorldUpdate();
}

void Icon::Render()
{
	if (!is_active)return;
	VS->Set();
	PS->Set();

	WB->SetVS(0);
	CB->SetPS(0);

	clips[clip_idx]->Render();
}

void Icon::PostRender()
{
}

void Icon::SetState(UI::UI_STATE state)
{
}

void Icon::SetID(UI::UI_ID id)
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
	}
		break;
	case UI::UI_ID::SKILL_ICON:
		break;
	case UI::UI_ID::WEAPON_ICON_BACK:
		break;
	case UI::UI_ID::BUFF_ICON_BACK:
		break;
	default:
		break;
	}
}
