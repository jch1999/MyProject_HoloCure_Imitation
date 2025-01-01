#pragma once
class SkillSelector :public UI
{
protected:
	static vector<shared_ptr<const Frame>>& GetSkillSelectorFrames();
	static int& GetSkillSelectorUseCnt();

public:
	SkillSelector(Vector2 inSize = Vector2(386.0f, 69.0f), Vector2 inScale = Vector2(1.0f, 1.0f), Vector2 inOffset = Vector2(0.0f, 0.0f));
	~SkillSelector();


	// UI을(를) 통해 상속됨
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;
	virtual void InitFrame() override;
	virtual void ClearFrame() override;

	virtual void SetID(UI::UI_ID id) override;
	void SetSkillID(int skillId);
	int GetSkillID() { return skillId; }
	const SkillIcon* GetIcon() { return skillIcon; }
	const TextPrinter* GetNameText() { return skillNameText; }
	const TextPrinter* GetScriptText() { return skillScriptText; }
	void SetIconOffset(Vector2 offset) { return skillIcon->SetOffset(offset); }
	void SetNameTOffset(Vector2 offset) { return skillNameText->SetOffset(offset); }
	void SetScriptTOffset(Vector2 offset) { return skillScriptText->SetOffset(offset); }
	void SetText();
	void SetText(string& nameStr, string& scriptStr);

protected:
	// Skill::SKILL_ID sId;
	int skillId;
	SkillIcon* skillIcon;
	//vector<Text*> text_vec;
	TextPrinter* skillNameText;
	TextPrinter* skillScriptText;
	int lineLength;
	Vector2 charInterval;
	Vector2 charPos;
	Vector2 charSize;
	Vector2 nameOffset;
	Vector2 scriptOffset;
};