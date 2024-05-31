#pragma once
class LevelUpPanel :public UI
{
protected:
	// Level UP! �� ���� �ؽ�Ʈ
	Text* levelUp_text;
	// Player �̹����� ��� �̹���
	Icon* player_full_icon;

	// ������ ���� �������� ��� â -- �� ������ ĭ�� ������ ����� �� â�� �ϵ��� ������ ����
	vector<SkillSelector*> skill_selectors;

	// ������ ��ȣ
	int select_idx;

public:
	LevelUpPanel();
	~LevelUpPanel();


	// UI��(��) ���� ��ӵ�
	virtual void Update() override;

	virtual void Render() override;

	virtual void PostRender() override;
	virtual void SetState(UI::UI_STATE state);
	virtual void SetID(UI::UI_ID id) override;
	virtual void SetActive(bool active) override;
};