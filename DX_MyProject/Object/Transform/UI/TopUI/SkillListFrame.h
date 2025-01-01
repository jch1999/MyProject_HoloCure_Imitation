#pragma once
class SkillListFrame :public UI
{
protected:
	static shared_ptr<const Frame>& GetSkillListFrameFrame();
	static int& GetSkillListFrameUseCnt();

protected:
	vector<SkillIcon*> weaponIconList;
	vector<SkillIcon*> buffIconList;

public:
	SkillListFrame(Vector2 inSize = Vector2(199.0f, 86.0f), Vector2 inScale = Vector2(2.0f, 2.0f), Vector2 inOffset = Vector2(180, 85));;
	~SkillListFrame();


	// UI을(를) 통해 상속됨
	virtual void Update() override;
	virtual void Render() override;
	virtual void InitFrame() override;
	virtual void ClearFrame() override;

	virtual void SetID(UI::UI_ID id) override { this->id = id; }
};