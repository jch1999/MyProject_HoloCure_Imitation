#pragma once
class StudyGlasses :public Buff
{
protected:

public:
	StudyGlasses();
	~StudyGlasses();


	// Buff��(��) ���� ��ӵ�
	virtual bool LevelDown() override;

	virtual void Update() override;

	virtual void Render() override;

	virtual void PostRender() override;

	virtual bool LevelUp() override;

};