#pragma once
class IconFrame :public UI
{
protected:
	
public:
	IconFrame();
	~IconFrame();


	// UI��(��) ���� ��ӵ�
	virtual void Update() override;

	virtual void Render() override;

	virtual void PostRender() override;
	virtual void SetState(UI::UI_STATE state) { this->state = state; }
	virtual void SetID(UI::UI_ID id) override { this->id = id; }
};