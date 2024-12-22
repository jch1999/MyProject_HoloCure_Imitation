#pragma once
class Arrow :public UI
{
protected:
	static vector<shared_ptr<const Frame>>& GetArrowFrames();
	static int& GetArrowUseCnt();

public:
	Arrow(Vector2 size = Vector2(64.0f, 64.0f), Vector2 scale = Vector2(1, 1), Vector2 offset = Vector2(0, 0));
	~Arrow();


	// UI을(를) 통해 상속됨
	virtual void Update() override;
	virtual void Render() override;
	virtual void InitFrame() override;
	virtual void ClearFrame() override;
	
	virtual void SetState(UI::UI_STATE state);
	virtual void SetID(UI::UI_ID id) override;

};