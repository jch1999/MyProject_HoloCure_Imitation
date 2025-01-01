#pragma once
class Panel;
class LevelUpPanel;
class EnhancePanel;
class ExitPanel;
class RewardPanel;
class TextPrinter;
class UIManager :public Singleton<UIManager>
{
private:
	UIManager();
	~UIManager();

public:
	friend class Singleton;

	void Update();
	void Render();
	void PostRneder();

	const vector<UI*>& GetUIList(int idx) { return uiList[idx]; }
	UI* GenerateUI(UI::UI_ID id, Transform* t = nullptr, Vector2 size = Vector2(1, 1), Vector2 offset = Vector2(0, 0));
	UI* GetUI(UI::UI_ID id);
	void SetPlayer(Player* p) { player = p; }
	Player* GetPlayer() { return player; }
	void AddUI(UI* ui,int idx) { uiList[idx].push_back(ui); }
	UI::UI_TYPE IDToType(UI::UI_ID id);

	void ResetPanel();

	EnhancePanel* GetEnhancePanel() { return enhancePanel; }
	void ActivateEnhancePanel();
	void DeactivateEnhancePanel();
	
	ExitPanel* GetExitPanel() { return exitPanel; }
	void IncreaseLevelUpCnt();
	void DecreaseLevelUpCnt();

	RewardPanel* GetRewardPanel() { return rewardPanel; }
	void ActivateRewardPanel();
	void DeactivateRewardPanel();

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
	vector<vector<UI*>> uiList;

private:
	Panel* nowPanel;// LevelUp, Enhance, Reward panel - player, anvil, reward box���� Ȱ��, �ϳ��� Ȱ���Ǿ��� �� �ٸ� �ϳ��� Ȱ���� �ȵ�.
	// Ȱ����⸦ ���� � ���� Ȱ����������� ����ص� ������ �ʿ�...? ȣ���� ��ü�� �����Ϳ� � â�� ȣ���Ϸ��� ���� �˱� ���� enum class ����?
	// list vector .. list?
	UI* pausePanel;
	LevelUpPanel* levelPanel;
	EnhancePanel* enhancePanel;
	ExitPanel* exitPanel;
	RewardPanel* rewardPanel;
	TextPrinter* lvText, * ctrText;

	// â ��� ����
	int levelUpCnt;
	bool isEnhance;
	bool isReward;

};