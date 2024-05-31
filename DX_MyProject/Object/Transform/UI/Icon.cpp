#include "framework.h"

Icon::Icon()
{
	vector<wstring> files =
	{
		// PlayerIcon & Defulat Weapon Skill Icon
		L"Textures/Player/PC Computer - HoloCure - Save the Fans - Amelia Watson_rm_bg.png",
		L"Textures/Player/PC Computer - HoloCure - Save the Fans - Takanashi Kiara_rm_bg.png",
		L"Textures/Player/PC Computer - HoloCure - Save the Fans - Hakos Baelz_rm_bg.png",
		// Back Icon
		L"Textures/UI/PC Computer - HoloCure - Save the Fans - Game Menus and HUDs_rm_bg.png",
		// Skill Icon
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

	// Weapon Icon Back
	frames.push_back(new Frame(files[3], 139, 567, 12, 11));
	clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP, 1));
	frames.clear();

	// Buff Icon Back
	frames.push_back(new Frame(files[3], 153, 567, 12, 11));
	clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP, 1));
	frames.clear();

	// Default Weapon Icon
	// PistolShot
	// Normal
	frames.push_back(new Frame(files[0], 11, 1956, 18, 20));
	clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP, 1));
	frames.clear();
	// Awake
	frames.push_back(new Frame(files[0], 34, 1956, 24, 25));
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
	frames.push_back(new Frame(files[2], 9, 703, 21, 20));
	clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP, 1));
	frames.clear();
	// Awake
	frames.push_back(new Frame(files[2], 33, 703, 25, 20));
	clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP, 1));
	frames.clear();

	// Weapon Skill Icon

	// Buff Skill Icon

	// Level Label
	label = new LevelLabel();
	label->SetTarget(this);
	label->SetOffset(Vector2(0, 30));
	label->SetActive(false);

	child_list.push_back(label);

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

	scale = clips[clip_idx]->GetFrameSize() * ui_size / clips[clip_idx]->GetFrameOriginSize() * ui_scale * additional_scale;
	clips[clip_idx]->Update();

	pos = target->pos + offset;
	WorldUpdate();

	if (id != UI_ID::PLAYER_ICON)
	{
		// 레이블 정보 갱신을 위한 내용이 SetID에 있으니 일단은 그것을 그대로 사용
		SetID(this->id);
	}

	for (auto child : child_list)
		child->Update();
}

void Icon::Render()
{
	if (!is_active)return;
	VS->Set();
	PS->Set();

	WB->SetVS(0);
	CB->SetPS(0);

	clips[clip_idx]->Render();

	for (auto child : child_list)
		child->Render();
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
		CB->data.colour = Float4(1.0f, 1.0f, 1.0f, 1.0f);
		label->SetActive(false);
	}
		break;
	case UI::UI_ID::SKILL_ICON:
	{
		switch (skill_id)
		{
			// WEAPON SKILL
		case (int)Skill::SKILL_ID::PISTOL_SHOT:
		case (int)Skill::SKILL_ID::PHOENIX_SWORD:
		case (int)Skill::SKILL_ID::PLAY_DICE:
		{
			int level = SkillManager::Get()->GetSkillByID(Skill::SKILL_ID(skill_id))->GetLevel();
			if (level == 7)
			{
				clip_idx = 5 + skill_id * 2 + 1;
			}
			else
			{
				clip_idx = 5 + skill_id * 2;
			}
			label->SetClipIdx(2);
		}
			break;
		case (int)Skill::SKILL_ID::HOLO_BOMB:
		{
			int level = SkillManager::Get()->GetSkillByID(Skill::SKILL_ID(skill_id))->GetLevel();
			if (level == 7)
			{
				label->SetClipIdx(1);
			}
			else
			{
				label->SetClipIdx(0);
			}
		}
			break;
		case (int)Skill::SKILL_ID::ELITE_LAVA_BUCKET:
		{
			int level = SkillManager::Get()->GetSkillByID(Skill::SKILL_ID(skill_id))->GetLevel();
			if (level == 7)
			{
				label->SetClipIdx(1);
			}
			else
			{
				label->SetClipIdx(0);
			}

		}
			break;
		case (int)Skill::SKILL_ID::PSYCHO_AXE:
		{
			int level = SkillManager::Get()->GetSkillByID(Skill::SKILL_ID(skill_id))->GetLevel();
			if (level == 7)
			{
				label->SetClipIdx(1);
			}
			else
			{
				label->SetClipIdx(0);
			}

		}
			break;
		case (int)Skill::SKILL_ID::SPIDER_COOKING:
		{
			int level = SkillManager::Get()->GetSkillByID(Skill::SKILL_ID(skill_id))->GetLevel();
			if (level == 7)
			{
				label->SetClipIdx(1);
			}
			else
			{
				label->SetClipIdx(0);
			}

		}
			break;
		default:
			break;
		}
		// label->SetActive(true);
		CB->data.colour = Float4(1.0f, 1.0f, 1.0f, 1.0f);
	}
		break;
	case UI::UI_ID::WEAPON_ICON_BACK:
	{
		clip_idx = 3;
		label->SetActive(false);
		CB->data.colour = Float4(0.8f, 0.8f, 0.8f, 0.3f);
	}
		break;
	case UI::UI_ID::BUFF_ICON_BACK:
	{
		clip_idx = 4;
		label->SetActive(false);
		CB->data.colour = Float4(0.8f, 0.8f, 0.8f, 0.3f);
	}
		break;
	default:
		break;
	}
}
