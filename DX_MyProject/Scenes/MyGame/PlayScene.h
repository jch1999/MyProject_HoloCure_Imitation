#pragma once
class PlayScene :public Scene
{
private:
	Player* player;

public:
	PlayScene();
	~PlayScene();

	// Scene��(��) ���� ��ӵ�
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;
};