#pragma once
class SkillListFrame :public UI
{
protected:
	vector<Icon*> weaponIconList;
	vector<Icon*> buffIconList;

public:
	SkillListFrame();
	~SkillListFrame();


	// UI을(를) 통해 상속됨
	virtual void Update() override;

	virtual void Render() override;

	virtual void PostRender() override;
	virtual void SetState(UI::UI_STATE state) { this->state = state; }
	virtual void SetID(UI::UI_ID id) override { this->id = id; }
};