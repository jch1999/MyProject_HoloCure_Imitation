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
	}type;
	enum class  UI_ID
	{
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
		// Selecor
		SELECTOR,
		// Timer
		TIMER,
		//Counter
		COUNTER,
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

	vector<UI*> child_list;

	Vector2 ui_size;
	Vector2 ui_scale;
	Vector2 additional_scale;
	vector<Clip*> clips; // 애니메이션 클립들
	int clip_idx;

public:
	UI();
	virtual ~UI();

	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void PostRender() = 0;

	void SetTarget(Transform* target) { this->target = target; }
	const Transform* GetTarget() { return target; }
	void SetSize(Vector2 size) { this->ui_size = size; }
	const Vector2& GetSize() { return ui_size; }
	void SetScale(Vector2 scale) { this->ui_scale = scale; }
	const Vector2& GetScale() { return ui_scale; }
	void SetAddtionalScale(Vector2 scale) { this->additional_scale = scale; }
	const Vector2& GetAdditionalScale() { return additional_scale; }
	void SetOffset(Vector2 offset) { this->offset = offset; }
	const Vector2& GetOffset() { return offset; }
	void AddOffset(Vector2 offset) { this->offset = this->offset + offset; }
	virtual void SetState(UI::UI_STATE state) = 0;
	virtual void SetID(UI::UI_ID id) = 0;
	virtual void SetActive(bool active) { is_active = active; }
	void SetClipIdx(int idx) { clip_idx = idx; }
	void SetColor(Float4 color) { CB->data.colour = color; }
};