#pragma once
class HoloBomb :public Weapon
{
public:
	HoloBomb();
	~HoloBomb();

	// Skill을(를) 통해 상속됨
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;
	virtual bool LevelUp() override;
	virtual bool LevelDown() override;

	void UpdateBomb();
};