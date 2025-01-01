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
	LevelUpPanel(Vector2 inSize = Vector2(WIN_WIDTH, WIN_HEIGHT), Vector2 inScale = Vector2(21.0f, 1.0f), Vector2 inOffset = WIN_CENTER);
	~LevelUpPanel();


	// UI��(��) ���� ��ӵ�
	virtual void Update() override;

	virtual void Render() override;
	virtual void PostRender() override;

	virtual void SetActive(bool active) override;
	void SetSkillSelector();
};