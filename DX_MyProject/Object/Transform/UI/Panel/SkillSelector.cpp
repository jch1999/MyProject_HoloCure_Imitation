#include "framework.h"

vector<shared_ptr<const Frame>>& SkillSelector::GetSkillSelectorFrames()
{
	static vector<shared_ptr<const Frame>> skillSelectorFrames;
	return skillSelectorFrames;
}

int& SkillSelector::GetSkillSelectorUseCnt()
{
	static int skillSelectorUseCnt = 0;
	return skillSelectorUseCnt;
}

SkillSelector::SkillSelector(Vector2 inSize, Vector2 inScale, Vector2 inOffset)
	:UI(inSize, inScale, inOffset)
	, charPos(Vector2(0,0)),charInterval(Vector2(10.0f,20.0f)), lineLength(40)
	,nameOffset(Vector2(-230.0f,-35.0f))
	,scriptOffset(Vector2(-180.0f,-10.0f))
{
	if (GetSkillSelectorFrames().empty())
	{
		InitFrame();
	}

	skillIcon = new SkillIcon();
	skillIcon->SetID(UI_ID::SKILL_LEVEL_UP_ICON);
	skillIcon->SetTarget(this);
	skillIcon->SetOffset(Vector2(-215.0f, 5.0f));
	skillIcon->SetActive(true);
	
	childList.push_back(skillIcon);

	// text 
	skillNameText = new TextPrinter();
	skillNameText->SetTarget(this);
	skillNameText->SetOffset(nameOffset);
	skillNameText->SetCharInterval(charInterval);
	skillNameText->SetLineLength(lineLength);
	skillNameText->SetCharScale(Vector2(0.3f, 0.3f));

	skillScriptText = new TextPrinter();
	skillScriptText->SetTarget(this);
	skillScriptText->SetOffset(scriptOffset);
	skillScriptText->SetCharInterval(charInterval);
	skillScriptText->SetLineLength(lineLength);
	skillScriptText->SetCharScale(Vector2(0.3f, 0.3f));

	childList.push_back(skillNameText);
	childList.push_back(skillScriptText);

	id = UI::UI_ID::SELECTOR;
	type = UI::UI_TYPE::SELECTOR;
	state = UI::UI_STATE::IDLE;
	additionalScale = Vector2(1, 1);
	is_active = false;

	++GetSkillSelectorUseCnt();
}

SkillSelector::~SkillSelector()
{
	if ((--GetSkillSelectorUseCnt()) == 0)
	{
		ClearFrame();
	}
}

void SkillSelector::Update()
{
	if (!is_active)return;

	auto& currentFrame = GetSkillSelectorFrames()[clipIdx];
	scale = currentFrame->GetFrameSize() * uiSize / currentFrame->GetFrameOriginSize() * uiScale * additionalScale;

	pos = target->pos + offset;
	WorldUpdate();

	for (auto child : childList)
		child->Update();
}

void SkillSelector::Render()
{
	if (!is_active)return;
	VS->Set();
	PS->Set();

	WB->SetVS(0);
	CB->SetPS(0);

	GetSkillSelectorFrames()[clipIdx]->Render();

	for (auto child : childList)
		child->Render();
}

void SkillSelector::PostRender()
{
	ImGui::Text("Now Skill ID : %d", skillId);
}

void SkillSelector::InitFrame()
{
	auto& skillSelectorFrames = GetSkillSelectorFrames();
	if (!(skillSelectorFrames.empty())) return;

	wstring file = L"Textures/UI/PC Computer - HoloCure - Save the Fans - Game Menus and HUDs_rm_bg.png";

	// unselect clip
	skillSelectorFrames.emplace_back(make_shared<const Frame>(file, 4.0f, 2049.0f, 386.0f, 69.0f));

	// select clip
	skillSelectorFrames.emplace_back(make_shared<const Frame>(file, 4.0f, 1979.0f, 386.0f, 69.0f));
}

void SkillSelector::ClearFrame()
{
	GetSkillSelectorFrames().clear();
}

void SkillSelector::SetID(UI::UI_ID id)
{
	this->id = id;
}

void SkillSelector::SetSkillID(int skillId)
{
	this->skillId = skillId;
	skillIcon->SetSkillID(skillId);
	
	SetText();
}

void SkillSelector::SetText()
{
	int textIdx = 0;
	if (skillId != -1)
	{
		Skill* skill = SkillManager::Get()->GetSkillByID((Skill::SKILL_ID)skillId);
		

		if (skill->GetLevelUpAble())
		{
			string name = skill->GetSkillName() + " LV "+ to_string(skill->GetLevel() + 1);
			string scripts = skill->GetScript();
			if (scripts.length() > 120)
			{
				skillScriptText->SetTextInfo(Vector2(0.25f, 0.25f), charInterval * 0.7f, 60);
			}
			else
			{
				skillScriptText->SetTextInfo(Vector2(0.3f, 0.3f), charInterval, 40);
			}
			skillNameText->SetText(name);
			skillScriptText->SetText(scripts);
			skillNameText->SetActive(true);
			skillScriptText->SetActive(true);
		}
		else
		{
			string name = skill->GetSkillName() + " LV MAX";
			skillNameText->SetText(name);
			skillNameText->SetActive(true);
			skillScriptText->SetActive(false);
		}
		skillIcon->SetActive(true);
	}
	else
	{
		skillIcon->SetActive(false);
		skillNameText->SetActive(false);
		skillScriptText->SetActive(false);
	}
}

void SkillSelector::SetText(string& nameStr, string& scriptStr)
{
	skillNameText->SetText(nameStr);
	skillScriptText->SetText(scriptStr);
	skillNameText->SetActive(true);
	skillScriptText->SetActive(true);
}
