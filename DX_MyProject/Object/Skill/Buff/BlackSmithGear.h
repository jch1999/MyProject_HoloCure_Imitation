#pragma once
class BlackSmithGear :public Buff
{
protected:

public:
	BlackSmithGear();
	~BlackSmithGear();



	// Buff��(��) ���� ��ӵ�
	virtual bool LevelDown() override;

	virtual void Update() override;

	virtual void Render() override;

	virtual void PostRender() override;

	virtual bool LevelUp() override;

};