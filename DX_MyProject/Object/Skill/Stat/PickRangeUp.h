#pragma once
class PickRangeUp :public Skill
{
private:

public:
	PickRangeUp();
	~PickRangeUp();

	// Skill을(를) 통해 상속됨
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;
	virtual bool LevelUp() override;
	virtual bool LevelDown() override;

	// Skill을(를) 통해 상속됨
	virtual bool GetEnhanceAble() override;
	virtual bool Enhance() override;
};