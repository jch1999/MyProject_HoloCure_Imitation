#pragma once
class LevelUpPanel :public Panel
{
protected:
	// Level UP! 을 띄우는 텍스트
	LevelText* levelUpText;

	// 레벨업 보상 선택지를 띄울 창 -- 각 선택지 칸의 보관과 출력은 이 창이 하도록 구현할 예정
	vector<SkillSelector*> skillSelectors;

	// 선택지 번호
	int selectIdx;

public:
	LevelUpPanel(Vector2 inSize = Vector2(WIN_WIDTH, WIN_HEIGHT), Vector2 inScale = Vector2(21.0f, 1.0f), Vector2 inOffset = WIN_CENTER);
	~LevelUpPanel();


	// UI을(를) 통해 상속됨
	virtual void Update() override;

	virtual void Render() override;
	virtual void PostRender() override;

	virtual void SetActive(bool active) override;
	void SetSkillSelector();
};