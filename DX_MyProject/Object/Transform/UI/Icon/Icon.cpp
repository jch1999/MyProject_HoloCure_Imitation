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
		L"Textures/Skill/PC Computer - HoloCure - Save the Fans - Item Icons_rm_bg.png",
	};
	vector<shared_ptr<const Frame>> frames;

	// Player Icon
	// Watson
	frames.emplace_back(make_shared<const Frame>(files[0], 10, 2363, 43, 38));
	clips.emplace_back(make_shared<Clip>(frames, Clip::CLIP_TYPE::LOOP, 1));
	frames.clear();
	// Kiara
	frames.emplace_back(make_shared<const Frame>(files[1], 10, 3953, 43, 38));
	clips.emplace_back(make_shared<Clip>(frames, Clip::CLIP_TYPE::LOOP, 1));
	frames.clear();
	// Baelz
	frames.emplace_back(make_shared<const Frame>(files[2], 10, 802, 43, 38));
	clips.emplace_back(make_shared<Clip>(frames, Clip::CLIP_TYPE::LOOP, 1));
	frames.clear();

	// Player Full Icon
	// Watson
	frames.emplace_back(make_shared<const Frame>(files[0], 7, 2419, 73, 105));
	clips.emplace_back(make_shared<Clip>(frames, Clip::CLIP_TYPE::LOOP, 1));
	frames.clear();
	// Kiara
	frames.emplace_back(make_shared<const Frame>(files[1], 7, 4008, 63, 115));
	clips.emplace_back(make_shared<Clip>(frames, Clip::CLIP_TYPE::LOOP, 1));
	frames.clear();
	// Baelz
	frames.emplace_back(make_shared<const Frame>(files[2], 7, 858, 73, 112));
	clips.emplace_back(make_shared<Clip>(frames, Clip::CLIP_TYPE::LOOP, 1));
	frames.clear();
	
	// Weapon Icon Back
	frames.emplace_back(make_shared<const Frame>(files[3], 139, 567, 12, 11));
	clips.emplace_back(make_shared<Clip>(frames, Clip::CLIP_TYPE::LOOP, 1));
	frames.clear();

	// Buff Icon Back
	frames.emplace_back(make_shared<const Frame>(files[3], 153, 567, 12, 11));
	clips.emplace_back(make_shared<Clip>(frames, Clip::CLIP_TYPE::LOOP, 1));
	frames.clear();

	// Default Weapon Icon
	// PistolShot
	// Normal
	frames.emplace_back(make_shared<const Frame>(files[0], 11, 1956, 18, 20));
	clips.emplace_back(make_shared<Clip>(frames, Clip::CLIP_TYPE::LOOP, 1));
	frames.clear();
	// Awake
	frames.emplace_back(make_shared<const Frame>(files[0], 34, 1956, 24, 25));
	clips.emplace_back(make_shared<Clip>(frames, Clip::CLIP_TYPE::LOOP, 1));
	frames.clear();
	// PhoenixSword
	// Normal
	frames.emplace_back(make_shared<const Frame>(files[1], 8, 3683, 22, 21));
	clips.emplace_back(make_shared<Clip>(frames, Clip::CLIP_TYPE::LOOP, 1));
	frames.clear();
	// Awake
	frames.emplace_back(make_shared<const Frame>(files[1], 33, 3684, 25, 25));
	clips.emplace_back(make_shared<Clip>(frames, Clip::CLIP_TYPE::LOOP, 1));
	frames.clear();
	// PlayDice
	// Normal
	frames.emplace_back(make_shared<const Frame>(files[2], 9, 703, 21, 20));
	clips.emplace_back(make_shared<Clip>(frames, Clip::CLIP_TYPE::LOOP, 1));
	frames.clear();
	// Awake
	frames.emplace_back(make_shared<const Frame>(files[2], 33, 703, 25, 20));
	clips.emplace_back(make_shared<Clip>(frames, Clip::CLIP_TYPE::LOOP, 1));
	frames.clear();

	// Weapon Skill Icon
	// HOLO_BOMB:
	frames.emplace_back(make_shared<const Frame>(files[4], 139, 52, 25, 20));
	clips.emplace_back(make_shared<Clip>(frames, Clip::CLIP_TYPE::LOOP, 1));
	frames.clear();
	// ELITE_LAVA_BUCKET:
	frames.emplace_back(make_shared<const Frame>(files[4], 31, 52, 25, 20));
	clips.emplace_back(make_shared<Clip>(frames, Clip::CLIP_TYPE::LOOP, 1));
	frames.clear();
	
	// PSYCHO_AXE:
	frames.emplace_back(make_shared<const Frame>(files[4], 166, 52, 25, 20));
	clips.emplace_back(make_shared<Clip>(frames, Clip::CLIP_TYPE::LOOP, 1));
	frames.clear();

	// BOUNCE_BALL:
	frames.emplace_back(make_shared<const Frame>(files[4], 58, 76, 25, 22));
	clips.emplace_back(make_shared<Clip>(frames, Clip::CLIP_TYPE::LOOP, 1));
	frames.clear();

	// CEO_TEAR:
	frames.emplace_back(make_shared<const Frame>(files[4], 58, 52, 25, 22));
	clips.emplace_back(make_shared<Clip>(frames, Clip::CLIP_TYPE::LOOP, 1));
	frames.clear();
	
	// SPIDER_COOKING:
	frames.emplace_back(make_shared<const Frame>(files[4], 4, 52, 25, 20));
	clips.emplace_back(make_shared<Clip>(frames, Clip::CLIP_TYPE::LOOP, 1));
	frames.clear();
	
	// Buff Skill Icon
	// NURSE_HORN
	frames.emplace_back(make_shared<const Frame>(files[4], 31.0f, 224.0f, 25.0f, 20.0f));
	clips.emplace_back(make_shared<Clip>(frames, Clip::CLIP_TYPE::LOOP, 1));
	frames.clear();
	// FULL_MEAL
	frames.emplace_back(make_shared<const Frame>(files[4], 58.0f, 224.0f, 25.0f, 20.0f));
	clips.emplace_back(make_shared<Clip>(frames, Clip::CLIP_TYPE::LOOP, 1));
	frames.clear();
	// PIKIPIK_PIMAN
	frames.emplace_back(make_shared<const Frame>(files[4], 112.0f, 224.0f, 25.0f, 22.0f));
	clips.emplace_back(make_shared<Clip>(frames, Clip::CLIP_TYPE::LOOP, 1));
	frames.clear();
	// STUDY_GLASSES
	frames.emplace_back(make_shared<const Frame>(files[4], 139.0f, 248.0f, 25.0f, 20.0f));
	clips.emplace_back(make_shared<Clip>(frames, Clip::CLIP_TYPE::LOOP, 1));
	frames.clear();
	// SUPER_CHATTO_TIME
	frames.emplace_back(make_shared<const Frame>(files[4], 4.0f, 272.0f, 25.0f, 20.0f));
	clips.emplace_back(make_shared<Clip>(frames, Clip::CLIP_TYPE::LOOP, 1));
	frames.clear();
	// BLACKSMITH_GEAR
	frames.emplace_back(make_shared<const Frame>(files[4], 31.0f, 272.0f, 25.0f, 22.0f));
	clips.emplace_back(make_shared<Clip>(frames, Clip::CLIP_TYPE::LOOP, 1));
	frames.clear();
	// NINJA_HEADBAND
	frames.emplace_back(make_shared<const Frame>(files[4], 4.0f, 176.0f, 25.0f, 22.0f));
	clips.emplace_back(make_shared<Clip>(frames, Clip::CLIP_TYPE::LOOP, 1));
	frames.clear();

	// Stat Skill Icon
	// MAX_HP ATK SPD CRT PICK_UP
	for (int i = 0; i < 5; i++)
	{
		frames.emplace_back(make_shared<const Frame>(files[4], 4.0f +i *27.0f, 322.0f, 25.0f, 25.0f));
		clips.emplace_back(make_shared<Clip>(frames, Clip::CLIP_TYPE::LOOP, 1));
		frames.clear();
	}
	// Extra Skill Icon
	// COIN
	frames.emplace_back(make_shared<const Frame>(files[4], 200.0f, 322.0f, 15.0f, 15.0f));
	clips.emplace_back(make_shared<Clip>(frames, Clip::CLIP_TYPE::LOOP, 1));
	frames.clear();
	// FOOD
	frames.emplace_back(make_shared<const Frame>(files[4], 166.0f, 322.0f, 32.0f, 32.0f));
	clips.emplace_back(make_shared<Clip>(frames, Clip::CLIP_TYPE::LOOP, 1));
	frames.clear();
	// EXP
	//frames.emplace_back(make_shared<const Frame>(files[4], 4.0f, 322.0f, 25.0f, 25.0f));
	//clips.emplace_back(make_shared<Clip>(frames, Clip::CLIP_TYPE::LOOP, 1));
	//frames.clear();
	
	// Level Label
	label = new LevelLabel();
	label->SetTarget(this);
	label->SetOffset(Vector2(0, 30));
	label->SetActive(false);

	child_list.push_back(label);

	// Icon Frame
	icon_frame = new IconFrame();
	icon_frame->SetTarget(this);
	icon_frame->SetScale(Vector2(1.5f, 1.5f));
	icon_frame->SetActive(false);

	child_list.push_back(icon_frame);

	id = UI::UI_ID::PLAYER_ICON;
	type = UI::UI_TYPE::ICON;
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

void Icon::InitFrame()
{
}

void Icon::ClearFrame()
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
		icon_frame->SetActive(false);
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
		label->SetActive(false);
		icon_frame->SetActive(false);
	}
	break;
	case UI::UI_ID::SKILL_ICON:
	{
		switch (skill_id)
		{
			// DEFAULT WEAPON SKILL
		case (int)Skill::SKILL_ID::PISTOL_SHOT:
		case (int)Skill::SKILL_ID::PHOENIX_SWORD:
		case (int)Skill::SKILL_ID::PLAY_DICE:
		{
			int level = SkillManager::Get()->GetSkillByID(Skill::SKILL_ID(skill_id))->GetLevel();
			if (level == 7)
			{
				clip_idx = 8 + skill_id * 2 + 1;
			}
			else
			{
				clip_idx = 8 + skill_id * 2;
			}
			label->SetClipIdx(2);
			label->SetLevel(level);
		}
			break;
		// WEAPON & BUFF SKILL
		case (int)Skill::SKILL_ID::HOLO_BOMB:
		case (int)Skill::SKILL_ID::ELITE_LAVA_BUCKET:
		case (int)Skill::SKILL_ID::PSYCHO_AXE:
		case (int)Skill::SKILL_ID::BOUNCE_BALL:
		case (int)Skill::SKILL_ID::CEO_TEAR:
		case (int)Skill::SKILL_ID::SPIDER_COOKING:
		case (int)Skill::SKILL_ID::NURSE_HORN:
		case (int)Skill::SKILL_ID::FULL_MEAL:
		case (int)Skill::SKILL_ID::PIKIPIK_PIMAN:
		case (int)Skill::SKILL_ID::STUDY_GLASSES:
		case (int)Skill::SKILL_ID::SUPER_CHATTO_TIME:
		case (int)Skill::SKILL_ID::BLACKSMITH_GEAR:
		case (int)Skill::SKILL_ID::NINJA_HEADBAND:
		{
			int level = SkillManager::Get()->GetSkillByID(Skill::SKILL_ID(skill_id))->GetLevel();
			if (!SkillManager::Get()->GetSkillByID(Skill::SKILL_ID(skill_id))->GetLevelUpAble())
			{
				label->SetClipIdx(1);
			}
			else
			{
				label->SetClipIdx(0);
			}
			label->SetLevel(level);
			clip_idx = 14 + (int)(skill_id)-(int)(Skill::SKILL_ID::HOLO_BOMB);
		}
			break;
		{

		}
		default:
			break;
		}
		// label->SetActive(true);
		CB->data.colour = Float4(1.0f, 1.0f, 1.0f, 1.0f);
		icon_frame->SetActive(false);
		SetSize(Vector2(43.0f, 38.0f));
	}
		break;
	case UI::UI_ID::SKILL_LEVEL_UP_ICON:
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
				clip_idx = 8 + skill_id * 2 + 1;
			}
			else
			{
				clip_idx = 8 + skill_id * 2;
			}
			icon_frame->SetActive(true);
			icon_frame->SetClipIdx(0);
		}
		break;
		case (int)Skill::SKILL_ID::HOLO_BOMB:
		case (int)Skill::SKILL_ID::ELITE_LAVA_BUCKET:
		case (int)Skill::SKILL_ID::PSYCHO_AXE:
		case (int)Skill::SKILL_ID::BOUNCE_BALL:
		case (int)Skill::SKILL_ID::CEO_TEAR:
		case (int)Skill::SKILL_ID::SPIDER_COOKING:
		{
			clip_idx = 14 + (int)(skill_id)-(int)(Skill::SKILL_ID::HOLO_BOMB);
			icon_frame->SetActive(true);
			icon_frame->SetClipIdx(0);
		}
		break;
		case (int)Skill::SKILL_ID::NURSE_HORN:
		case (int)Skill::SKILL_ID::FULL_MEAL:
		case (int)Skill::SKILL_ID::PIKIPIK_PIMAN:
		case (int)Skill::SKILL_ID::STUDY_GLASSES:
		case (int)Skill::SKILL_ID::SUPER_CHATTO_TIME:
		case (int)Skill::SKILL_ID::BLACKSMITH_GEAR:
		case (int)Skill::SKILL_ID::NINJA_HEADBAND:
		{
			clip_idx = 14 + (int)(skill_id)-(int)(Skill::SKILL_ID::HOLO_BOMB);
			icon_frame->SetActive(true);
			icon_frame->SetClipIdx(1);
		}
		break;
		case (int)Skill::SKILL_ID::MAX_HP:
		case (int)Skill::SKILL_ID::ATK:
		case (int)Skill::SKILL_ID::SPD:
		case (int)Skill::SKILL_ID::CRT:
		case (int)Skill::SKILL_ID::PICK_UP:
		{
			clip_idx = 14 + (int)(skill_id)-(int)(Skill::SKILL_ID::HOLO_BOMB);
			icon_frame->SetActive(true);
			icon_frame->SetClipIdx(2);
		}
		break;
		case (int)Skill::SKILL_ID::COIN:
		case (int)Skill::SKILL_ID::FOOD:
		{
			clip_idx = 14 + (int)(skill_id)-(int)(Skill::SKILL_ID::HOLO_BOMB);
			icon_frame->SetActive(true);
			icon_frame->SetClipIdx(3);
		}
		default:
			break;
		}
		CB->data.colour = Float4(1.0f, 1.0f, 1.0f, 1.0f);
		SetSize(Vector2(43.0f, 38.0f));
	}
		break;
	case UI::UI_ID::SKILL_ENHANCE_ICON:
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
				clip_idx = 8 + skill_id * 2 + 1;
			}
			else
			{
				clip_idx = 8 + skill_id * 2;
			}
		}
		break;
		case (int)Skill::SKILL_ID::HOLO_BOMB:
		case (int)Skill::SKILL_ID::ELITE_LAVA_BUCKET:
		case (int)Skill::SKILL_ID::PSYCHO_AXE:
		case (int)Skill::SKILL_ID::BOUNCE_BALL:
		case (int)Skill::SKILL_ID::CEO_TEAR:
		case (int)Skill::SKILL_ID::SPIDER_COOKING:
		{
			clip_idx = 14 + (int)(skill_id)-(int)(Skill::SKILL_ID::HOLO_BOMB);
		}
		break;
		default:
			break;
		}
		CB->data.colour = Float4(1.0f, 1.0f, 1.0f, 1.0f);
		icon_frame->SetActive(false);
		SetSize(Vector2(43.0f, 38.0f));
	}
		break;
	case UI::UI_ID::WEAPON_ICON_BACK:
	{
		clip_idx = 6;
		label->SetActive(false);
		CB->data.colour = Float4(0.8f, 0.8f, 0.8f, 0.3f);
		SetSize(Vector2(43.0f, 38.0f));
	}
		break;
	case UI::UI_ID::BUFF_ICON_BACK:
	{
		clip_idx = 7;
		label->SetActive(false);
		CB->data.colour = Float4(0.8f, 0.8f, 0.8f, 0.3f);
		SetSize(Vector2(43.0f, 38.0f));
	}
		break;
	default:
		break;
	}
}
