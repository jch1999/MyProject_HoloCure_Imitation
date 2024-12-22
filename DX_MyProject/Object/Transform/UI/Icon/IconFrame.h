#pragma once
class IconFrame :public UI
{
protected:
	static vector<shared_ptr<const Frame>>&  GetIconFrameFrames();
	static int& GetIconFrameUseCnt();

public:
	IconFrame(Vector2 inSize = Vector2(35.0f, 36.0f), Vector2 inScale = Vector2(1.0f, 1.0f), Vector2 inOffset = Vector2(3.0f, 3.0f));
	~IconFrame();


	// UI을(를) 통해 상속됨
	virtual void Update() override;
	virtual void Render() override;
	virtual void InitFrame() override;
	virtual void ClearFrame() override;

	virtual void SetState(UI::UI_STATE state) { this->state = state; }
	virtual void SetID(UI::UI_ID id) override { this->id = id; }
};