#pragma once
class SkillIcon :public UI
{
protected:
	static vector<shared_ptr<const Frame>>& GetSkillIconFrames();
	static int& GetSkillIconUseCnt();

protected:
	// Skill::SKILL_ID s_id;
	int skill_id;
	LevelLabel* label;
	IconFrame* icon_frame;

public:
	SkillIcon(Vector2 inSize = Vector2(43.0f, 38.0f), Vector2 inScale = Vector2(1, 1), Vector2 inOffset = Vector2(0, 0));
	~SkillIcon();

	// UI을(를) 통해 상속됨
	virtual void Update() override;
	virtual void Render() override;
	virtual void InitFrame() override;
	virtual void ClearFrame() override;

	virtual void SetID(UI::UI_ID id);
	void SetSkillID(int skill_id);
	FORCEINLINE const int GetSkillID() { return skill_id; }
	void SetLabelActive(bool active);
	FORCEINLINE const LevelLabel* GetLabel() { return label; }
	const IconFrame* GetFrame() { return icon_frame; }
};