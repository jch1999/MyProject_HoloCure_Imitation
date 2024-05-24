#pragma once
class PistolShot :public Skill
{
private:
	float proj_delay;
	float now_proj_delay;
	int projCnt;

	vector<int> hitLimt_table;
public:
	PistolShot();
	~PistolShot();

	// Skill을(를) 통해 상속됨
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;
};