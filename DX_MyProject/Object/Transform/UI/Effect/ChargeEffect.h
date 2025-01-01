#pragma once
class ChargeEffect :public UI
{
protected:
	static vector<shared_ptr<const Frame>>& GetChangeEffectFrames();
	static int& GetChangeEffectUseCnt();

public:
	ChargeEffect(Vector2 inSize = Vector2(128.0f, 128.0f), Vector2 inScale = Vector2(1.0f, 1.0f), Vector2 inOffset = Vector2(0.0f, 0.0f));
	~ChargeEffect();

	// UI을(를) 통해 상속됨
	virtual void Update() override;

	virtual void Render() override;

	virtual void PostRender() override;

	virtual void InitFrame() override;

	virtual void ClearFrame() override;

	virtual void SetState(UI::UI_STATE state);

	virtual void SetID(UI::UI_ID id);

};