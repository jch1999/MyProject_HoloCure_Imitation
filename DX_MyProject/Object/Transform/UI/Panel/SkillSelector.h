#pragma once
class SkillSelector :public UI
{
protected:
	// Skill::SKILL_ID s_id;
	int skill_id;
	SkillIcon* skill_icon;

public:
	SkillSelector();
	~SkillSelector();


	// UI을(를) 통해 상속됨
	virtual void Update() override;

	virtual void Render() override;

	virtual void PostRender() override;
	virtual void SetState(UI::UI_STATE state);
	virtual void SetID(UI::UI_ID id) override;
	void SetSkillID(int skill_id);
	int GetSkillID() { return skill_id; }
	const SkillIcon* GetIcon() { return skill_icon; }
};