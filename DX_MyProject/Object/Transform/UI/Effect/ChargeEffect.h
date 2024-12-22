#pragma once
class ChargeEffect :public UI
{
protected:
	static vector<shared_ptr<const Frame>>& GetChangeEffectFrames();
	static int& GetChangeEffectUseCnt();

public:
	ChargeEffect();
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