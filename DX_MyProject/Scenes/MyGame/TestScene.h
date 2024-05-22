#pragma once
class TestScene :public Scene
{
private:
	Player* player;
	Skill* skill;
	Projectile* proj;
	Enemy* enemy;
	Item* item;
	HPBar* hpBar;
public:
	TestScene();
	~TestScene();

	// Scene��(��) ���� ��ӵ�
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;
};