#pragma once
class Heal :public Skill
{
private:

public:
	Heal();
	~Heal();

	// Skill을(를) 통해 상속됨
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;
	virtual bool LevelUp() override;
	virtual bool LevelDown() override;

	// Skill을(를) 통해 상속됨
	virtual bool GetEnhanceAble() override;
	virtual void Enhance() override;
};