#pragma once
class PauseBack :public UI
{
protected:
	static shared_ptr<const Frame>& GetPauseBackFrame();
	static int& GetPauseBackUseCnt();

public:
	PauseBack(Vector2 inSize = Vector2(WIN_WIDTH, WIN_HEIGHT), Vector2 inScale = Vector2(1.0f, 1.0f), Vector2 inOffset = Vector2(0.0f, 0.0f));
	~PauseBack();


	// UI을(를) 통해 상속됨
	virtual void Update() override;
	virtual void Render() override;
	virtual void InitFrame() override;
	virtual void ClearFrame() override;

	virtual void SetID(UI::UI_ID id) override;
};