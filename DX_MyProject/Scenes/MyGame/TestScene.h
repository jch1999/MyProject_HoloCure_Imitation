#pragma once
class TestScene :public Scene
{
private:
	Player* player;

public:
	TestScene();
	~TestScene();

	// Scene을(를) 통해 상속됨
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;
};