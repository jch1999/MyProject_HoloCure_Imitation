#pragma once
class FullMeal :public Buff
{
protected:

public:
	FullMeal();
	~FullMeal();

	// Buff��(��) ���� ��ӵ�
	virtual bool LevelDown() override;

	virtual void Update() override;

	virtual void Render() override;

	virtual void PostRender() override;

	virtual bool LevelUp() override;

};