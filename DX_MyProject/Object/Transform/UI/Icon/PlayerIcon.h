#pragma once
class PlayerIcon :public UI
{
protected:

public:
	PlayerIcon();
	~PlayerIcon();

	// UI��(��) ���� ��ӵ�
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;
	virtual void SetState(UI::UI_STATE state);
	virtual void SetID(UI::UI_ID id);
};