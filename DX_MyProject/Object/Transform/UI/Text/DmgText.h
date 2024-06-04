#pragma once
class DmgText :public UI
{
protected:
	Vector2 move_dir;

	float leftTime;
	float lifeTime;
	float speed;

public:
	DmgText();
	~DmgText();


	// UI을(를) 통해 상속됨
	virtual void Update() override;

	virtual void Render() override;

	virtual void PostRender() override;
	virtual void SetState(UI::UI_STATE state) override { this->state = state; }
	virtual void SetID(UI::UI_ID id) override { this->id = id; }

	void SetLifeTime(float time) { lifeTime = time; }
	void SetMoveDir(Vector2 dir) { move_dir = dir; }
	void SetPos(Vector2 spawnPos) { pos = spawnPos; }
	void SetClipIdx(int idx);
	virtual void SetActive(bool active);
};