#pragma once
class Icon :public UI
{
protected:
	// Skill::SKILL_ID s_id;
	int skill_id;
	LevelLabel* label;
	IconFrame* icon_frame;

public:
	Icon();
	~Icon();


	// UI을(를) 통해 상속됨
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;
	virtual void InitFrame() override;
	virtual void ClearFrame() override;

	virtual void SetState(UI::UI_STATE state);
	virtual void SetID(UI::UI_ID id) override;
	void SetSkillID(int skill_id) { this->skill_id = skill_id; }
	void SetLabelActive(bool active) { label->SetActive(active); }
	const LevelLabel* GetLabel() { return label; }
	const IconFrame* GetFrame() { return icon_frame; }
};