#pragma once
class Buff :public Skill
{
protected:

public:
	Buff(SKILL_ID id, int maxLevel = 5);
	virtual ~Buff();

	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void PostRender() = 0;

	virtual bool LevelUp() = 0;
	virtual bool GetEnhanceAble() { return GetLevelUpAble(); }
	virtual bool Enhance();
};