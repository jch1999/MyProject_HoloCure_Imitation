#pragma once
class Panel;
class LevelUpPanel;
class EnhancePanel;
class ExitPanel;
class TextPrinter;
class UIManager :public Singleton<UIManager>
{
private:
	Player* player;
public:
	// ��ü UI�� ����Ʈ
	// vector<UI*> ui_list;
	// ���� ������ ������ ����
	// 0 filed_back(dmgText) 
	// 1 field_front & Camera(hp_bar, arrow, exp_bar, player icon) 
	// 2 pause black_effect
	// 3 panels(level up, enhance, reward, pause) -> pause panel�� ������ �ٸ� �г��� ���� ���� ȣ���� �� �ֵ��� ����
	// pause panel�� Ȱ��ȭ�Ǿ� ���� ���� �ٸ� panel�̳� UI�� ����? UI_Pasue ��� ������ ������ �ϳ�?
	vector<vector<UI*>> ui_list;

	Panel* nowPanel;// LevelUp, Enhance, Reward panel - player, anvil, reward box���� Ȱ��, �ϳ��� Ȱ���Ǿ��� �� �ٸ� �ϳ��� Ȱ���� �ȵ�.
	// Ȱ����⸦ ���� � ���� Ȱ����������� ����ص� ������ �ʿ�...? ȣ���� ��ü�� �����Ϳ� � â�� ȣ���Ϸ��� ���� �˱� ���� enum class ����?
	// list vector .. list?
	UI* pausePanel;
	LevelUpPanel* levelPanel;
	EnhancePanel* enhancePanel;
	ExitPanel* exitPanel;
	TextPrinter* lv_text, *ctr_text;

	// â ��� ����
	int levelUpCnt;
	bool isEnhance;

private:
	UIManager();
	~UIManager();

public:
	friend class Singleton;

	void Update();
	void Render();
	void PostRneder();

	const vector<UI*>& GetUIList(int idx) { return ui_list[idx]; }
	UI* GenerateUI(UI::UI_ID id, Transform* t = nullptr, Vector2 size = Vector2(1, 1), Vector2 offset = Vector2(0, 0));
	UI* GetUI(UI::UI_ID id);
	void SetPlayer(Player* p) { player = p; }
	Player* GetPlayer() { return player; }
	void AddUI(UI* ui,int idx) { ui_list[idx].push_back(ui); }
	UI::UI_TYPE IDToType(UI::UI_ID id);
};