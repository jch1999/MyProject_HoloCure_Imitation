#pragma once
class DmgText :public SpecialText
{
protected:
	Vector2 moveDir;

	float nowTime;
	float lifeTime;
	float speed;

public:
	DmgText();
	~DmgText();


	// UI을(를) 통해 상속됨
	virtual void Update() override;

	virtual void Render() override;

	virtual void PostRender() override;
	virtual void SetID(UI::UI_ID id) override;

	void SetLifeTime(float inTime) { lifeTime = inTime; }
	void SetMoveDir(Vector2 dir) { moveDir = dir; }
	void SetPos(Vector2 spawnPos) { pos = spawnPos; }
	void SetClipIdx(int idx);
	virtual void SetActive(bool active);
};