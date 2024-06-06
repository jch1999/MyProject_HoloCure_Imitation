#pragma once
class EnhancePanel :public Panel
{
protected:
	// UPGRADE! �� ���� �ؽ�Ʈ
	TextPrinter* upgrade_text;
	// ���� ���� ��ų���� ǥ���� ������ ����Ʈ
	// 0 weaponIcon_list
	// 1 buffIcon_list
	vector<vector<SkillIcon*>> skillIcon_list;


	// ������ ���� �������� ��� â -- �� ������ ĭ�� ������ ����� �� â�� �ϵ��� ������ ����
	SkillSelector* selector;

	// ������ ��ȣ
	int select_type;
	int select_idx;

public:
	EnhancePanel();
	~EnhancePanel();

	// UI��(��) ���� ��ӵ�
	virtual void Update() override;

	virtual void Render() override;
	virtual void PostRender() override;

	virtual void SetActive(bool active) override;
};