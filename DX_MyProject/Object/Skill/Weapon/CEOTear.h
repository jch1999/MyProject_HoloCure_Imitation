#pragma once
class CEOTear :public Weapon
{
private:
	float projDelay;
	float nowProjDelay;
	int projCnt;

public:
	CEOTear();
	~CEOTear();


	void UpdateTears();

	// Weapon��(��) ���� ��ӵ�
	virtual bool LevelDown() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;
	virtual bool LevelUp() override;
};