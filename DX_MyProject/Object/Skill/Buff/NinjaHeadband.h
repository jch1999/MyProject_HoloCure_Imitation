#pragma once
class NinjaHeadband :public Buff
{
protected:

public:
	NinjaHeadband();
	~NinjaHeadband();



	// Buff을(를) 통해 상속됨
	virtual bool LevelDown() override;

	virtual void Update() override;

	virtual void Render() override;

	virtual void PostRender() override;

	virtual bool LevelUp() override;

};