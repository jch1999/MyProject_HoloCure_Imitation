#pragma once
class ExpBar :public UI
{
protected:
	float expRate;
	Vector2 bar_size;
public:
	ExpBar();
	~ExpBar();


	// UI��(��) ���� ��ӵ�
	virtual void Update() override;

	virtual void Render() override;

	virtual void PostRender() override;
	virtual void SetState(UI::UI_STATE state);
	virtual void SetID(UI::UI_ID id) override;
	void SetExpRate(float rate);
};