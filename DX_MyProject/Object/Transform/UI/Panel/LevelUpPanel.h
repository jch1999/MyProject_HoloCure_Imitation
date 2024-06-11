#pragma once
class LevelUpPanel :public Panel
{
protected:
	// Level UP! �� ���� �ؽ�Ʈ
	LevelText* levelUpText;

	// ������ ���� �������� ��� â -- �� ������ ĭ�� ������ ����� �� â�� �ϵ��� ������ ����
	vector<SkillSelector*> skillSelectors;

	// ������ ��ȣ
	int selectIdx;

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