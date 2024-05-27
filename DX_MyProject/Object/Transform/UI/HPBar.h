#pragma once
class HPBar :public UI
{
protected:
	float hpRate;

public:
	HPBar();
	~HPBar();


	// UI��(��) ���� ��ӵ�
	virtual void Update() override;

	virtual void Render() override;

	virtual void PostRender() override;
	virtual void SetState(UI::UI_STATE state);
	virtual void SetID(UI::UI_ID id) override;
	void SetHpRate(float rate);
};