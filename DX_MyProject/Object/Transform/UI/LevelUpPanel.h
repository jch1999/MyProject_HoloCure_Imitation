#pragma once
class LevelUpPanel :public Panel
{
protected:
	// Level UP! �� ���� �ؽ�Ʈ
	LevelText* levelUp_text;
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

	virtual void SetActive(bool active) override;
	void SetSkillSelector();
};