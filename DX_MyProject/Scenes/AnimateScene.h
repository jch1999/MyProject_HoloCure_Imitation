#pragma once
class AnimateScene :public Scene
{
private:
	AnimatePlayer* player;

public:
	AnimateScene();
	~AnimateScene();

	// Scene��(��) ���� ��ӵ�
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;
};