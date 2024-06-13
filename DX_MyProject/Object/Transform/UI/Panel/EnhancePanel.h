#pragma once
class EnhancePanel :public Panel
{
protected:
	// UPGRADE! 을 띄우는 텍스트
	TextPrinter* upgradeText;
	// 소유 중인 스킬들을 표시할 아이콘 리스트
	// 0 weaponIcon_list
	// 1 buffIcon_list
	vector<vector<SkillIcon*>> skillIconList;

	Anvil* usedAnvil;
	// 선택된 스킬의 정보를 출력할 셀렉터
	SkillSelector* selector;
	// 강화 가능할 때는 확률을, 불가능할 때는 불가능한 이유(코인 부족) 출력
	TextPrinter* enhanceRateText; 
	Button* btn;

	// 선택지 번호
	// 스킬 선택지
	int selectIdx;
	bool selected;

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