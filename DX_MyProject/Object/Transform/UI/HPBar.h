#pragma once
class HPBar :public UI
{
protected:
	Vector2 size;
	Frame* frame;
	float leftTime;
public:
	HPBar();
	~HPBar();


	// UI을(를) 통해 상속됨
	virtual void Update() override;

	virtual void Render() override;

	virtual void PostRender() override;
	virtual void SetState(UI::UI_STATE state);
	virtual void SetID(UI::UI_ID id) override;

	void SetLifeTime(float time) { leftTime = time; }
};