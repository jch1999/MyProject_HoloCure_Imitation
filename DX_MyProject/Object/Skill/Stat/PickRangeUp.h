#pragma once
class PickRangeUp :public Skill
{
private:

public:
	PickRangeUp();
	~PickRangeUp();

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