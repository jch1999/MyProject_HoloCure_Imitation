#pragma once
class HoloBomb :public Weapon
{
public:
	HoloBomb();
	~HoloBomb();

	// Skill��(��) ���� ��ӵ�
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;
	virtual bool LevelUp() override;
	virtual bool LevelDown() override;

	void UpdateBomb();
};