#pragma once
class PikiPikiPiman :public Buff
{
protected:
	float per_rate;
	float now_addRate;
public:
	PikiPikiPiman();
	~PikiPikiPiman();


	// Buff��(��) ���� ��ӵ�
	virtual bool LevelDown() override;

	virtual void Update() override;

	virtual void Render() override;

	virtual void PostRender() override;

	virtual bool LevelUp() override;

};