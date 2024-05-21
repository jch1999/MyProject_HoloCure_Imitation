#pragma once
class HPBar :public UI
{
protected:
	Vector2 size;
	Frame* frame;
public:
	HPBar();
	~HPBar();


	// UI을(를) 통해 상속됨
	virtual void Update() override;

	virtual void Render() override;

	virtual void PostRender() override;

	virtual void Respawn() override;

	void SetSize(Vector2 s) { size = s; }
};