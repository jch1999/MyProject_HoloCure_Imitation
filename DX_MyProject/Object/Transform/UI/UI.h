#pragma once
class UI :public Transform
{

public:
	enum class UI_TYPE
	{
		TEXT,
		DMG_TEXT,
		LABEL,
		IMAGE,
		ICON,
		BUTTON,
		FRAME,
		PANEL,
		HP_BAR,
		EXP_BAR,
		ARROW,
		SELECTOR,
		TIMER,
		COUNTER,
		EFFECT
	}type;
	enum class  UI_ID
	{
		//IMAGE
		IMAGE,
		// Text
		TEXT,
		LEVEL_TEXT,
		TEXT_PRINTER,
		// Dmg Text
		DMG_TEXT,
		CRT_DMG_TEXT,
		PLAYER_DMG_TEXT,
		LEVEL_LABEL,
		// Hp Bar
		HP_BAR,
		HP_BAR_BACK,
		// Exp Bar
		EXP_BAR_BACK,
		EXP_BAR,
		EXP_BAR_FRONT,
		// Frame
		PLAYER_ICON_FRAME,
		SKILL_LIST_FRAME,
		SKILL_ICON_FRAME,
		// Icon
		PLAYER_ICON,
		PLAYER_FULL_ICON,
		SKILL_ICON,
		SKILL_LEVEL_UP_ICON,
		SKILL_ENHANCE_ICON,
		WEAPON_ICON_BACK,
		BUFF_ICON_BACK,
		COUNTER_ICON,
		STAT_ICON,
		// Button
		BUTTON,
		// Arrow
		ATK_ARROW,
		ATK_ARROW_FIXED,
		// Panel
		LEVEL_UP_PANEL,
		ENHANCE_PANEL,
		REWARD_PANEL,
		PAUSE_PANEL, 
		EXIT_PANEL,
		// Selecor
		SELECTOR,
		// Timer
		TIMER,
		//Counter
		COUNTER,
		// Effect
		CHARGE_EFFECT
	}id;
	enum class UI_STATE
	{
		IDLE, // 존재는 하나 현재 사용중이진 않음 -> update - o render - x
		ACTIVE // 사용중 -> update - o render - o
	}state;

protected:
	VertexShader* VS;
	PixelShader* PS;
	ColourBuffer* CB;

	Transform* target;
	Vector2 offset;

	vector<UI*> childList;

	Vector2 uiSize;
	Vector2 uiScale;
	Vector2 additionalScale;
	vector<shared_ptr<const Clip>> clips; // 애니메이션 클립들
	int clipIdx;
	shared_ptr<const Frame> frame; // 애니메이션이 필요없을 경우 Frame만 사용

public:
	UI();
	virtual ~UI();

	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void PostRender() = 0;
	virtual void SetState(UI::UI_STATE state) = 0;
	virtual void SetID(UI::UI_ID id) = 0;

	void SetTarget(Transform* target);
	FORCEINLINE const Transform* GetTarget() { return target; }

	void SetSize(Vector2 inSize);
	FORCEINLINE const Vector2& GetSize() { return uiSize; }
	
	void SetScale(Vector2 inScale);
	FORCEINLINE const Vector2& GetScale() { return uiScale; }
	
	void SetAddtionalScale(Vector2 inScale);
	FORCEINLINE const Vector2& GetAdditionalScale() { return additionalScale; }
	
	void SetOffset(Vector2 inOffset);
	void AddOffset(Vector2 inOffset);
	FORCEINLINE const Vector2& GetOffset() { return this->offset; }
	
	virtual void SetActive(bool inActive);
	virtual void SetClipIdx(int inIdx);
	virtual void SetColor(Float4 inColor);
};