#pragma once
class TestScene :public Scene
{
private:
	Player* player;

public:
	TestScene();
	~TestScene();

	// Scene��(��) ���� ��ӵ�
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;
};