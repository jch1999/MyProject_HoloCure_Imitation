#include "framework.h"

shared_ptr<const Frame>& SkillListFrame::GetSkillListFrameFrame()
{
	static shared_ptr<const Frame> skillListFrameFrame;
	return skillListFrameFrame;
}

int& SkillListFrame::GetSkillListFrameUseCnt()
{
	static int skillListFrameUseCnt = 0;
	return skillListFrameUseCnt;
}

SkillListFrame::SkillListFrame(Vector2 inSize, Vector2 inScale, Vector2 inOffset)
	:UI(inSize, inScale, inOffset)
{
	if (GetSkillListFrameFrame() == nullptr)
	{
		InitFrame();
	}

	// 자식 UI 생성 - Weapon Skill Icon 6개 , Buff Skill Icon 6개
	// Weapon Skill Icon
	Vector2 initOffset = Vector2(-75, -15);
	for (int i = 0; i < 6; i++)
	{
		SkillIcon* weaponIcon = new SkillIcon();
		weaponIcon->SetTarget(this);
		if (i == 0)
		{
			Skill::SKILL_ID sId = (*(SkillManager::Get()->nowWeaponList.begin()))->id;
			weaponIcon->SetSkillID((int)sId);
			weaponIcon->SetID(UI_ID::SKILL_ICON);
		}
		else
			weaponIcon->SetID(UI_ID::WEAPON_ICON_BACK);
		weaponIcon->SetOffset(initOffset + Vector2(50 * i, 0));
		weaponIcon->SetActive(true);

		weaponIconList.push_back(weaponIcon);
		childList.push_back(weaponIcon);
	}

	// Buff Skill Icon
	initOffset = Vector2(-75, 45);
	for (int i = 0; i < 6; i++)
	{
		SkillIcon* buffIcon = new SkillIcon();
		buffIcon->SetTarget(this);
		buffIcon->SetID(UI_ID::BUFF_ICON_BACK);
		buffIcon->SetOffset(initOffset + Vector2(50 * i, 0));
		buffIcon->SetActive(true);

		buffIconList.push_back(buffIcon);
		childList.push_back(buffIcon);
	}

	id = UI::UI_ID::SKILL_LIST_FRAME;
	type = UI::UI_TYPE::FRAME;
	state = UI::UI_STATE::IDLE;
	is_active = true;

	++GetSkillListFrameUseCnt();
}

SkillListFrame::~SkillListFrame()
{
	if ((--GetSkillListFrameUseCnt()) == 0)
	{
		ClearFrame();
	}
}

void SkillListFrame::Update()
{
	scale = GetSkillListFrameFrame()->GetFrameSize() * uiSize / GetSkillListFrameFrame()->GetFrameOriginSize() * uiScale;
	

	// 자식에 추가 작업 - weponList, buffList를 가져와 Icon 정보를 갱신하는 코드를 여기에
	vector<Skill*>& weaponList = (SkillManager::Get()->nowWeaponList);
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

	vector<Skill*>& buffList = (SkillManager::Get()->nowBuffList);
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

	for (auto ui : childList)
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

	GetSkillListFrameFrame()->Render();

	for (auto ui : childList)
		ui->Render();
}

void SkillListFrame::InitFrame()
{
	auto& frame = GetSkillListFrameFrame();
	
	if (frame) return;

	wstring file = L"Textures/UI/PC Computer - HoloCure - Save the Fans - Game Menus and HUDs_rm_bg.png";

	frame = make_shared<const Frame>(file, 4, 302, 199, 87);
}

void SkillListFrame::ClearFrame()
{
	GetSkillListFrameFrame().reset();
}
