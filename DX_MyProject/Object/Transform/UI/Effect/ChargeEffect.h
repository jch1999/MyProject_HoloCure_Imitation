#pragma once
class ChargeEffect :public UI
{
public:
	ChargeEffect();
	~ChargeEffect();



	// UI��(��) ���� ��ӵ�
	virtual void Update() override;

	virtual void Render() override;

	virtual void PostRender() override;

	virtual void SetState(UI::UI_STATE state);

	virtual void SetID(UI::UI_ID id);

};