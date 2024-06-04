#pragma once
class PlayScene :public Scene
{
private:
	Player* player;

public:
	PlayScene();
	~PlayScene();

	// Scene을(를) 통해 상속됨
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;
};