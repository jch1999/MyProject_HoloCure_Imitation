#pragma once
class Button :public UI
{
protected:
	static vector<shared_ptr<const Frame>>& GetButtonFrames();
	static int& GetButtonUseCnt();

protected:
	TextPrinter* btnText;
public:
	Button(Vector2 inSize = Vector2(180.0f, 30.0f), Vector2 inScale = Vector2(1.0f, 1.0f), Vector2 inOffset = Vector2(0.0f, 0.0f));
	virtual ~Button();



	// UI을(를) 통해 상속됨
	virtual void Update() override;

	virtual void Render() override;

	virtual void PostRender() override;

	virtual void InitFrame() override;

	virtual void ClearFrame() override;

	virtual void SetState(UI::UI_STATE state);

	virtual void SetID(UI::UI_ID id);

	TextPrinter* GetBtnText() { return btnText; }
};