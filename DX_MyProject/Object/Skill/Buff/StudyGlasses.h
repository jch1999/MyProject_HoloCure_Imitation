#pragma once
class StudyGlasses :public Buff
{
protected:

public:
	StudyGlasses();
	~StudyGlasses();


	// Buff을(를) 통해 상속됨
	virtual bool LevelDown() override;

	virtual void Update() override;

	virtual void Render() override;

	virtual void PostRender() override;

	virtual bool LevelUp() override;

};