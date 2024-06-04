#pragma once
class PlayerIconFrame :public UI
{
protected:
	PlayerIcon* playerIcon;
	HPBar* hpBar;
	HPBar* hpBar_back;
	// �ִ� hp�� 4�ڸ����� �� ���� ���� �״� text�� 7��(���� hp 3��, /�� 1��, �ִ� hp 3��) ����� ����
	Vector2 text_startOffset;
	vector<Text*> hpText;
public:
	PlayerIconFrame();
	~PlayerIconFrame();


	// UI��(��) ���� ��ӵ�
	virtual void Update() override;

	virtual void Render() override;

	virtual void PostRender() override;
	virtual void SetState(UI::UI_STATE state);
	virtual void SetID(UI::UI_ID id) override;
	void SetHpText();
};