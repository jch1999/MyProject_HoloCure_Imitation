#include "framework.h"

SkillListFrame::SkillListFrame()
{
	wstring file = L"Textures/UI/PC Computer - HoloCure - Save the Fans - Game Menus and HUDs_rm_bg.png";
	vector<Frame*> frames;
	frames.push_back(new Frame(file, 4, 302, 199, 87));
	clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP, 1.0f / 10.f));

	// 자식 UI 생성 - Weapon Skill Icon 6개 , Buff Skill Icon 6개
	// Weapon Skill Icon
	Vector2 initOffset = Vector2(-75, -15);
	for (int i = 0; i < 6; i++)
	{
		Icon* weaponIcon = new Icon();
		weaponIcon->SetTarget(this);
		if (i == 0)
		{
			Skill::SKILL_ID s_id = (*(SkillManager::Get()->nowWeapon_list.begin()))->id;
			weaponIcon->SetSkillID((int)s_id);
			weaponIcon->SetID(UI_ID::SKILL_ICON);
		}
		else
			weaponIcon->SetID(UI_ID::WEAPON_ICON_BACK);
		weaponIcon->SetOffset(initOffset + Vector2(50 * i, 0));
		weaponIcon->SetActive(true);

		weaponIconList.push_back(weaponIcon);
		child_list.push_back(weaponIcon);
	}

	// Buff Skill Icon
	initOffset = Vector2(-75, 45);
	for (int i = 0; i < 6; i++)
	{
		Icon* buffIcon = new Icon();
		buffIcon->SetTarget(this);
		buffIcon->SetID(UI_ID::BUFF_ICON_BACK);
		buffIcon->SetOffset(initOffset + Vector2(50 * i, 0));
		buffIcon->SetActive(true);

		buffIconList.push_back(buffIcon);
		child_list.push_back(buffIcon);
	}

	id = UI::UI_ID::SKILL_LIST_FRAME;
	type = UI::UI_TYPE::FRAME;
	state = UI::UI_STATE::IDLE;
	ui_size = Vector2(199.0f, 86.0f);
	ui_scale = Vector2(2.0f, 2.0f);
	offset = Vector2(180, 85);
	is_active = true;
}

SkillListFrame::~SkillListFrame()
{
}

void SkillListFrame::Update()
{
	scale = clips[clip_idx]->GetFrameSize() * ui_size / clips[clip_idx]->GetFrameOriginSize() * ui_scale;
	clips[0]->Update();

	// 자식에 추가 작업 - weponList, buffList를 가져와 Icon 정보를 갱신하는 코드를 여기에
	vector<Skill*>& weaponList = (SkillManager::Get()->nowWeapon_list);
	for (int i = 0; i < 6; i++)
	{
		int cnt = SkillManager::Get()->weaponCnt;
		if (i < SkillManager::Get()->weaponCnt)
		{
			weaponIconList[i]->SetID(UI_ID::SKILL_ICON);
			weaponIconList[i]->SetSkillID((int)weaponList[i]->id);
			weaponIconList[i]->SetLabelActive(true);
		}
		else
		{
			weaponIconList[i]->SetID(UI_ID::WEAPON_ICON_BACK);
		}
	}

	vector<Skill*>& buffList = (SkillManager::Get()->nowBuff_list);
	for (int i = 0; i < 6; i++)
	{
		if (i < SkillManager::Get()->buffCnt)
		{
			buffIconList[i]->SetID(UI_ID::SKILL_ICON);
			buffIconList[i]->SetSkillID((int)buffList[i]->id);
			buffIconList[i]->SetLabelActive(true);
		}
		else
		{
			buffIconList[i]->SetID(UI_ID::BUFF_ICON_BACK);
		}
	}

	pos = target->pos + offset;
	WorldUpdate();

	for (auto ui : child_list)
	{
		ui->Update();
	}
}

void SkillListFrame::Render()
{
	if (!is_active)return;

	VS->Set();
	PS->Set();

	WB->SetVS(0);
	CB->SetPS(0);

	clips[clip_idx]->Render();

	for (auto ui : child_list)
		ui->Render();
}

void SkillListFrame::PostRender()
{
}
