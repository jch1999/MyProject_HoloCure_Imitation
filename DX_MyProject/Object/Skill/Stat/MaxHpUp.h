#pragma once
class MaxHpUp :public Skill
{
private:

public:
	MaxHpUp();
	~MaxHpUp();

	// Skill��(��) ���� ��ӵ�
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;
	virtual bool LevelUp() override;
	virtual bool LevelDown() override;

	// Skill��(��) ���� ��ӵ�
	virtual bool GetEnhanceAble() override;
	virtual void Enhance(float enhanceAmount = 0.0f) override;
};