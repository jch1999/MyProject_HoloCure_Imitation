#pragma once
class Panel :public UI
{
protected:
	// Player �̹����� ��� �̹���
	PlayerIcon* player_full_icon;

	// ������ ��ȣ
	int selectIdx;

public:
	Panel(Vector2 inSize = Vector2(WIN_WIDTH, WIN_HEIGHT), Vector2 inScale = Vector2(21.0f, 1.0f), Vector2 inOffset = WIN_CENTER);
	~Panel();

	// UI��(��) ���� ��ӵ�
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;
	virtual void SetState(UI::UI_STATE state);
	virtual void SetID(UI::UI_ID id);
};