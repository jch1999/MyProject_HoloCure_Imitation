#pragma once
class EnhancePanel :public Panel
{
protected:
	// UPGRADE! 을 띄우는 텍스트
	TextPrinter* upgrade_text;
	// 소유 중인 스킬들을 표시할 아이콘 리스트
	// 0 weaponIcon_list
	// 1 buffIcon_list
	vector<vector<SkillIcon*>> skillIcon_list;

	Anvil* usedAnvil;
	// 레벨업 보상 선택지를 띄울 창 -- 각 선택지 칸의 보관과 출력은 이 창이 하도록 구현할 예정
	SkillSelector* selector;

	// 선택지 번호
	// 스킬 선택지
	int select_type;
	int select_idx;
	bool selected;
	int final_idx;

public:
	EnhancePanel();
	~EnhancePanel();

	// UI을(를) 통해 상속됨
	virtual void Update() override;

	virtual void Render() override;
	virtual void PostRender() override;

	virtual void SetActive(bool active) override;
	void SetAnvil(Anvil* anvil) { usedAnvil = anvil; }
	void ChoseSkill();
};