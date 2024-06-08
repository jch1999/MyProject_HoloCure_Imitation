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

	Anvil* usedAnvil;
	// ������ ���� �������� ��� â -- �� ������ ĭ�� ������ ����� �� â�� �ϵ��� ������ ����
	SkillSelector* selector;

	// ������ ��ȣ
	// ��ų ������
	int select_type;
	int select_idx;
	bool selected;
	int final_idx;

public:
	EnhancePanel();
	~EnhancePanel();

	// UI��(��) ���� ��ӵ�
	virtual void Update() override;

	virtual void Render() override;
	virtual void PostRender() override;

	virtual void SetActive(bool active) override;
	void SetAnvil(Anvil* anvil) { usedAnvil = anvil; }
	void ChoseSkill();
};