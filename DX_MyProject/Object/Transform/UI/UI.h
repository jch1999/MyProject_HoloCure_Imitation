#pragma once
class UI :public Transform
{

public:
	enum class UI_TYPE
	{
		DMG_TEXT,
		IMAGE,
		PANEL,
		HP_BAR,
		EXP_BAR,
		ARROW
	}type;
	enum class  UI_ID
	{
		// Dmg Text
		DMG_TEXT,
		CRT_DMG_TEXT,
		PLAYER_DMG_TEXT,
		// Hp Bar
		HP_BAR,
		HP_BAR_BACK,
		// Exp Bar
		EXP_BAR_BACK,
		EXP_BAR,
		EXP_BAR_FRONT,
		// Icon
		PLAYER_ICON,
		// Arrow
		ATK_ARROW,
		ATK_ARROW_FIXED
	}id;
	enum class UI_STATE
	{
		IDLE, // ����� �ϳ� ���� ��������� ���� -> update - o render - x
		ACTIVE // ����� -> update - o render - o
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

	vector<Clip*> clips; // �ִϸ��̼� Ŭ����
	int clip_idx;

public:
	UI();
	virtual ~UI();

	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void PostRender() = 0;
	void SetTarget(Transform* target) { this->target = target; }
	void SetScale(Vector2 scale) { this->ui_scale = scale; }
	void SetOffset(Vector2 offset) { this->offset = offset; }
	virtual void SetState(UI::UI_STATE state) = 0;
	virtual void SetID(UI::UI_ID id) = 0;
	virtual void SetActive(bool active) { is_active = active; }
};