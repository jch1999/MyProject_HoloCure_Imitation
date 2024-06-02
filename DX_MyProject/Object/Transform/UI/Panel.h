#pragma once
class Panel :public UI
{
protected:
	// Player �̹����� ��� �̹���
	Icon* player_full_icon;

	// ������ ��ȣ
	int select_idx;

public:
	Panel();
	~Panel();

	// UI��(��) ���� ��ӵ�
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;
	virtual void SetState(UI::UI_STATE state);
	virtual void SetID(UI::UI_ID id);
};