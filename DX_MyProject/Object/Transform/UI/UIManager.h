#pragma once
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
	// 3 panels(level up, enhance, pause)
	vector<vector<UI*>> ui_list;
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