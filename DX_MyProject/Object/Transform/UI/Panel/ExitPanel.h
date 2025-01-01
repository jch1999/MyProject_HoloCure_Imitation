#pragma once
class ExitPanel :public Panel
{
protected:
	ImageArea* popUp;
	vector<Button*> btns;
	TextPrinter* pauseText;
	int selectIdx;

public:
	ExitPanel(Vector2 inSize = Vector2(WIN_WIDTH, WIN_HEIGHT), Vector2 inScale = Vector2(1.0f, 1.0f), Vector2 inOffset = WIN_CENTER);
	~ExitPanel();

	// UI을(를) 통해 상속됨
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;
	virtual void SetActive(bool active)override;
};