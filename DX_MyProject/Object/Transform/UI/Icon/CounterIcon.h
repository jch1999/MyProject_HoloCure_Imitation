#pragma once
class CounterIcon :public UI
{
protected:
	static vector<shared_ptr<Frame>>& GetCounterIconFrames();
	static int& GetCounterIconUseCnt();

public:
	CounterIcon(Vector2 inSize = Vector2(15.0f, 15.0f), Vector2 inScale = Vector2(1.5f, 1.5f), Vector2 inOffset = Vector2(0.0f, 0.0f));
	~CounterIcon();

	// UI을(를) 통해 상속됨
	virtual void Update() override;
	virtual void Render() override;
	virtual void InitFrame() override;
	virtual void ClearFrame() override;

	virtual void SetID(UI::UI_ID id);
};