#pragma once
class NinjaHeadband :public Buff
{
protected:

public:
	NinjaHeadband();
	~NinjaHeadband();



	// Buff��(��) ���� ��ӵ�
	virtual bool LevelDown() override;

	virtual void Update() override;

	virtual void Render() override;

	virtual void PostRender() override;

	virtual bool LevelUp() override;

};