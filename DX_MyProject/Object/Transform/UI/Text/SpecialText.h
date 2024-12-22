#pragma once
class SpecialText :public UI
{
protected:
	static shared_ptr<Frame>& GetLevelUpFrame();
	static vector<vector<shared_ptr<const Frame>>>& GetNumberFrames();
	static int& GetTextUseCnt();

public:
	SpecialText(Vector2 inSize = Vector2(10.0f, 14.0f), Vector2 inScale = Vector2(1.0f, 1.0f), Vector2 inOffset = Vector2(0.0f, 0.0f));
	~SpecialText();


	// UI을(를) 통해 상속됨
	virtual void InitFrame() override;
	virtual void ClearFrame() override;

	virtual void SetState(UI::UI_STATE inState) override;
};