#pragma once
class UIManager :public Singleton<UIManager>
{
private:
	Player* player;
public:
	// 전체 UI의 리스트
	vector<UI*> ui_list;

private:
	UIManager();
	~UIManager();

public:
	friend class Singleton;

	void Update();
	void Render();
	void PostRneder();

	const vector<UI*>& GetUIList() { return ui_list; }
	void GenerateUI(UI::UI_ID id, Transform* t = nullptr, Vector2 offset = Vector2(0, 0));
	UI* GetUI(UI::UI_ID id);
	void SetPlayer(Player* p) { player = p; }
	void AddUI(UI* ui) { ui_list.push_back(ui); }
};