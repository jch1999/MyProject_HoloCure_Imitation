#include "framework.h"

vector<shared_ptr<const Frame>>& SkillIcon::GetSkillIconFrames()
{
	static vector<shared_ptr<const Frame>> skillIconFrames;
	return skillIconFrames;
}

int& SkillIcon::GetSkillIconUseCnt()
{
	static int skillIconUseCnt = 0;
	return skillIconUseCnt;
}

SkillIcon::SkillIcon(Vector2 inSize, Vector2 inScale, Vector2 inOffset)
	:UI(inSize, inScale, inOffset)
{
	if (GetSkillIconFrames().empty())
	{
		InitFrame();
	}
	// Level Label
	label = new LevelLabel();
	label->SetTarget(this);
	label->SetOffset(Vector2(0, 30));
	label->SetActive(false);

	childList.push_back(label);

	// Icon Frame
	icon_frame = new IconFrame();
	icon_frame->SetTarget(this);
	icon_frame->SetScale(Vector2(1.5f, 1.5f));
	icon_frame->SetActive(false);

	childList.push_back(icon_frame);

	id = UI::UI_ID::SKILL_ICON;
	type = UI::UI_TYPE::ICON;
	state = UI::UI_STATE::IDLE;
	is_active = false;

	++GetSkillIconUseCnt();
}

SkillIcon::~SkillIcon()
{
	if ((--GetSkillIconUseCnt()) == 0)
	{
		ClearFrame();
	}
}

void SkillIcon::Update()
{
	if (!is_active)return;

	if (clipIdx != -1)
	{
		auto& currentFrame = GetSkillIconFrames()[clipIdx];
		scale = currentFrame->GetFrameSize() * uiSize / currentFrame->GetFrameOriginSize() * uiScale * additionalScale;
	}

	if(target!=nullptr)
		pos = target->pos + offset;
	
	WorldUpdate();

	if (id != UI_ID::PLAYER_ICON)
	{
		// 레이블 정보 갱신을 위한 내용이 SetID에 있으니 일단은 그것을 그대로 사용
		SetID(this->id);
	}

	for (auto child : childList)
		child->Update();
}

void SkillIcon::Render()
{
	if (!is_active)return;
	VS->Set();
	PS->Set();

	WB->SetVS(0);
	CB->SetPS(0);

	if (clipIdx != -1)
	{
		GetSkillIconFrames()[clipIdx]->Render();
	}
	for (auto child : childList)
		child->Render();
}

void SkillIcon::InitFrame()
{
	auto& skillIconFrames = GetSkillIconFrames();
	if (!(skillIconFrames.empty())) return;

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

	// Weapon Icon Back
	skillIconFrames.emplace_back(make_shared<const Frame>(files[3], 139, 567, 12, 11));
	// Buff Icon Back
	skillIconFrames.emplace_back(make_shared<const Frame>(files[3], 153, 567, 12, 11));

	// Default Weapon Icon
	{
		// PistolShot
		// Normal
		skillIconFrames.emplace_back(make_shared<const Frame>(files[0], 11, 1956, 18, 20));
		// Awake
		skillIconFrames.emplace_back(make_shared<const Frame>(files[0], 34, 1956, 24, 25));
		// PhoenixSword
		// Normal
		skillIconFrames.emplace_back(make_shared<const Frame>(files[1], 8, 3683, 22, 21));
		// Awake
		skillIconFrames.emplace_back(make_shared<const Frame>(files[1], 33, 3684, 25, 25));
		// PlayDice
		// Normal
		skillIconFrames.emplace_back(make_shared<const Frame>(files[2], 9, 703, 21, 20));
		// Awake
		skillIconFrames.emplace_back(make_shared<const Frame>(files[2], 33, 703, 25, 20));
	}
	// Weapon Skill Icon
	{
		// HOLO_BOMB:
		skillIconFrames.emplace_back(make_shared<const Frame>(files[4], 139, 52, 25, 20));
		// ELITE_LAVA_BUCKET:
		skillIconFrames.emplace_back(make_shared<const Frame>(files[4], 31, 52, 25, 20));
		// PSYCHO_AXE:
		skillIconFrames.emplace_back(make_shared<const Frame>(files[4], 166, 52, 25, 20));
		// BOUNCE_BALL:
		skillIconFrames.emplace_back(make_shared<const Frame>(files[4], 58, 76, 25, 22));
		// CEO_TEAR:
		skillIconFrames.emplace_back(make_shared<const Frame>(files[4], 58, 52, 25, 22));
		// SPIDER_COOKING:
		skillIconFrames.emplace_back(make_shared<const Frame>(files[4], 4, 52, 25, 20));
	}
	// Buff Skill Icon
	{
		// NURSE_HORN
		skillIconFrames.emplace_back(make_shared<const Frame>(files[4], 31.0f, 224.0f, 25.0f, 20.0f));
		// FULL_MEAL
		skillIconFrames.emplace_back(make_shared<const Frame>(files[4], 58.0f, 224.0f, 25.0f, 20.0f));
		// PIKIPIK_PIMAN
		skillIconFrames.emplace_back(make_shared<const Frame>(files[4], 112.0f, 224.0f, 25.0f, 22.0f));
		// STUDY_GLASSES
		skillIconFrames.emplace_back(make_shared<const Frame>(files[4], 139.0f, 248.0f, 25.0f, 20.0f));
		// SUPER_CHATTO_TIME
		skillIconFrames.emplace_back(make_shared<const Frame>(files[4], 4.0f, 272.0f, 25.0f, 20.0f));
		// BLACKSMITH_GEAR
		skillIconFrames.emplace_back(make_shared<const Frame>(files[4], 31.0f, 272.0f, 25.0f, 22.0f));
		// NINJA_HEADBAND
		skillIconFrames.emplace_back(make_shared<const Frame>(files[4], 4.0f, 176.0f, 25.0f, 22.0f));
	}
	// Stat Skill Icon
	// MAX_HP ATK SPD CRT PICK_UP
	for (int i = 0; i < 5; i++)
	{
		skillIconFrames.emplace_back(make_shared<const Frame>(files[4], 4.0f + i * 27.0f, 322.0f, 25.0f, 25.0f));
	}
	// Extra Skill Icon
	{
		// COIN
		skillIconFrames.emplace_back(make_shared<const Frame>(files[4], 200.0f, 322.0f, 15.0f, 15.0f));
		// FOOD
		skillIconFrames.emplace_back(make_shared<const Frame>(files[4], 166.0f, 322.0f, 32.0f, 32.0f));
		// EXP
		//skillIconFrames.emplace_back(make_shared<const Frame>(files[4], 4.0f, 322.0f, 25.0f, 25.0f));
		//clips.push_back(new Clip(skillIconFrames, Clip::CLIP_TYPE::LOOP, 1));
		//skillIconFrames.clear();
	}
}

void SkillIcon::ClearFrame()
{
	GetSkillIconFrames().clear();
}


void SkillIcon::SetID(UI::UI_ID id)
{
	this->id = id;
	switch (id)
	{
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
				clipIdx = 2 + skill_id * 2 + 1;
			}
			else
			{
				clipIdx = 2 + skill_id * 2;
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
		case (int)Skill::SKILL_ID::MAX_HP:
		case (int)Skill::SKILL_ID::ATK:
		case (int)Skill::SKILL_ID::SPD:
		case (int)Skill::SKILL_ID::CRT:
		case (int)Skill::SKILL_ID::PICK_UP:
		case (int)Skill::SKILL_ID::COIN:
		case (int)Skill::SKILL_ID::FOOD:
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
			clipIdx = 8 + (int)(skill_id)-(int)(Skill::SKILL_ID::HOLO_BOMB);
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
				clipIdx = 2 + skill_id * 2 + 1;
			}
			else
			{
				clipIdx = 2 + skill_id * 2;
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
			clipIdx = 8 + (int)(skill_id)-(int)(Skill::SKILL_ID::HOLO_BOMB);
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
			clipIdx = 8 + (int)(skill_id)-(int)(Skill::SKILL_ID::HOLO_BOMB);
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
			clipIdx = 8 + (int)(skill_id)-(int)(Skill::SKILL_ID::HOLO_BOMB);
			icon_frame->SetActive(true);
			icon_frame->SetClipIdx(2);
		}
		break;
		case (int)Skill::SKILL_ID::COIN:
		case (int)Skill::SKILL_ID::FOOD:
		{
			clipIdx = 8 + (int)(skill_id)-(int)(Skill::SKILL_ID::HOLO_BOMB);
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
				clipIdx = 2 + skill_id * 2 + 1;
			}
			else
			{
				clipIdx = 2 + skill_id * 2;
			}
		}
		break;
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
		case (int)Skill::SKILL_ID::MAX_HP:
		case (int)Skill::SKILL_ID::ATK:
		case (int)Skill::SKILL_ID::SPD:
		case (int)Skill::SKILL_ID::CRT:
		case (int)Skill::SKILL_ID::PICK_UP:
		case (int)Skill::SKILL_ID::COIN:
		case (int)Skill::SKILL_ID::FOOD:
			clipIdx = 8 + (int)(skill_id)-(int)(Skill::SKILL_ID::HOLO_BOMB);
			break;
		default:
			clipIdx = -1;
			break;
		}
		CB->data.colour = Float4(1.0f, 1.0f, 1.0f, 1.0f); 
		icon_frame->SetActive(true);
		SetSize(Vector2(43.0f, 38.0f));
	}
	break;
	case UI::UI_ID::WEAPON_ICON_BACK:
	{
		clipIdx = 0;
		label->SetActive(false);
		CB->data.colour = Float4(0.8f, 0.8f, 0.8f, 0.3f);
		SetSize(Vector2(43.0f, 38.0f));
	}
	break;
	case UI::UI_ID::BUFF_ICON_BACK:
	{
		clipIdx = 1;
		label->SetActive(false);
		CB->data.colour = Float4(0.8f, 0.8f, 0.8f, 0.3f);
		SetSize(Vector2(43.0f, 38.0f));
	}
	break;
	default:
		break;
	}
}

void SkillIcon::SetSkillID(int skill_id)
{
	this->skill_id = skill_id;
}

void SkillIcon::SetLabelActive(bool active)
{
	label->SetActive(active);
}
