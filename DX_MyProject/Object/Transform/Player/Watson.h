#pragma once
class Watson :public Player
{
private:
	// 반격을 위한 피격정보 저장
	list<pair<Enemy*, float>> revengeList;
	bool isRevenge;
public:
	Watson(float MaxHP = 75.0f, float atk = 13.0f, float speed = 135.0f, float crt = 10.0f, float pickUpRange = 50.0f, float delay = 0.33f,Vector2 size=Vector2(24.0f,40.0f));
	~Watson();

	// Player을(를) 통해 상속됨
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;

	virtual void ChangeHP(float amount, Vector2 dir = Vector2(0, 0), Enemy* causer = nullptr);
	virtual void SetStatus(PLAYER_STATUS newStatus,UINT playOption=0) override;
	void AddRevenge(Enemy* e, float damage) { revengeList.push_back(make_pair(e, damage)); }
	const list<pair<Enemy*, float>> GetRevnegeList() { return revengeList; }
	void ClearRevengeList() { revengeList.clear(); }
	void SetRevenge(bool active) { isRevenge = active; }
};