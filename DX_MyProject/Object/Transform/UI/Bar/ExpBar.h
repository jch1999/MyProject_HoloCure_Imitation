#pragma once
class ExpBar :public UI
{
protected:
	static vector<shared_ptr<const Frame>>& GetExpBarFrames();
	static int& GetExpBarUseCtnt();

protected:
	float expRate;
	Vector2 bar_size;

public:
	ExpBar(Vector2 inSize = Vector2(WIN_WIDTH + 20.0f, 40.0f), Vector2 inScale = Vector2(1.0f, 1.0f), Vector2 inOffset = Vector2(WIN_CENTER_X + 10.0f, 20.0f));
	~ExpBar();


	// UI을(를) 통해 상속됨
	virtual void Update() override;
	virtual void Render() override;
	
	virtual void SetID(UI::UI_ID id) override;
	void SetExpRate(float rate);

	virtual void InitFrame() override;
	virtual void ClearFrame() override;
};