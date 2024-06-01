#pragma once
class CrtUp :public Skill
{
private:

public:
	CrtUp();
	~CrtUp();

	// Skill을(를) 통해 상속됨
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;
	virtual bool LevelUp() override;
	virtual bool LevelDown() override;

	// Skill을(를) 통해 상속됨
	virtual bool GetEnhanceAble() override;
	virtual void Enhance(float enhanceAmount = 0.0f) override;
};