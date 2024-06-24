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
	// 전체 UI의 리스트
	// vector<UI*> ui_list;
	// 랜더 순서로 나눠서 보관
	// 0 filed_back(dmgText) 
	// 1 field_front & Camera(hp_bar, arrow, exp_bar, player icon) 
	// 2 pause black_effect
	// 3 panels(level up, enhance, reward, pause) -> pause panel을 빼내서 다른 패널이 있을 때도 호출할 수 있도록 변경
	// pause panel이 활성화되어 있을 때는 다른 panel이나 UI도 정지? UI_Pasue 라는 변수를 만들어야 하나?
	vector<vector<UI*>> ui_list;

	Panel* nowPanel;// LevelUp, Enhance, Reward panel - player, anvil, reward box에서 활성, 하나가 활성되었을 때 다른 하나는 활성이 안됨.
	// 활성대기를 위해 어떤 것이 활성대기중인지 기록해둘 변수가 필요...? 호출한 객체의 포인터와 어떤 창을 호출하려는 건지 알기 위한 enum class 정도?
	// list vector .. list?
	UI* pausePanel;
	LevelUpPanel* levelPanel;
	EnhancePanel* enhancePanel;
	ExitPanel* exitPanel;
	TextPrinter* lv_text, *ctr_text;

	// 창 대기 여부
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