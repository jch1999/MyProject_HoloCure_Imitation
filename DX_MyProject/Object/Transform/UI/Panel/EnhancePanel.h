#pragma once
class EnhancePanel :public Panel
{
public:
	enum class ENHANCE_STATE
	{
		START,
		ENHANCING,
		END
	}enhance_state;
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
	ImageArea* coinImg;
	
	Button* btn;

	// 선택지 번호
	// 스킬 선택지
	int selectIdx;
	bool selected;
	bool isEnhancing;	// 강화 도중 - popUp창과 skill의 Icon, charge effect, 기타 anim 등 조작 여부
	
	ImageArea* popUp;
	SkillIcon* icon;
	TextPrinter* enhanceResultText;
	ChargeEffect* cEffect;
	LightEffect* sEffect;

	Vector2 iconOffset;
	float iconMoveSpd;
	bool isReturning;	// false이면 icon이 원점에서 멀어짐, true면 돌아옴
	float moveRot;		// icon의 이동각도
	float playTime, targetPlayTime;		// 애니메이션 재생 시간
	float moveTime, targetMoveTime;		// 이동시간, 매 방향전환 마다 다시 0으로 초기화
public:
	EnhancePanel();
	~EnhancePanel();

	// UI을(를) 통해 상속됨
	virtual void Update() override;

	virtual void Render() override;
	virtual void PostRender() override;

	virtual void SetActive(bool active) override;
	void SetAnvil(Anvil* anvil) { usedAnvil = anvil; }
	Anvil* const GetAnvil() { return usedAnvil; }
	void ChoseSkill();
	void PlayEnhancing();
	void EnhanceEnd();
};