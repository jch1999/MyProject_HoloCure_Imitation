#pragma once
class AnimateScene :public Scene
{
private:
	AnimatePlayer* player;

public:
	AnimateScene();
	~AnimateScene();

	// Scene을(를) 통해 상속됨
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;
};