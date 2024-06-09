#pragma once
class SkillSelector :public UI
{
protected:
	// Skill::SKILL_ID s_id;
	int skill_id;
	SkillIcon* skill_icon;
	//vector<Text*> text_vec;
	TextPrinter* skillName_text;
	TextPrinter* SkillScript_text;
	int line_length;
	Vector2 char_interval;
	Vector2 char_pos;
	Vector2 char_size;
	Vector2 name_offset;
	Vector2 script_offset;

public:
	SkillSelector();
	~SkillSelector();


	// UI��(��) ���� ��ӵ�
	virtual void Update() override;

	virtual void Render() override;

	virtual void PostRender() override;
	virtual void SetState(UI::UI_STATE state);
	virtual void SetID(UI::UI_ID id) override;
	void SetSkillID(int skill_id);
	int GetSkillID() { return skill_id; }
	const SkillIcon* GetIcon() { return skill_icon; }
	const TextPrinter* GetNameText() { return skillName_text; }
	const TextPrinter* GetScriptText() { return SkillScript_text; }
	void SetIconOffset(Vector2 offset) { return skill_icon->SetOffset(offset); }
	void SetNameTOffset(Vector2 offset) { return skillName_text->SetOffset(offset); }
	void SetScriptTOffset(Vector2 offset) { return SkillScript_text->SetOffset(offset); }
	void SetText();
};