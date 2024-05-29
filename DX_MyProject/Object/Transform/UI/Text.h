#pragma once
class Text :public UI
{
protected:

public:
	Text();
	~Text();


	// UI을(를) 통해 상속됨
	virtual void Update() override;

	virtual void Render() override;

	virtual void PostRender() override;
	virtual void SetState(UI::UI_STATE state) override { this->state = state; }
	virtual void SetID(UI::UI_ID id) override { this->id = id; }
	void SetClipIdx(int idx);
};