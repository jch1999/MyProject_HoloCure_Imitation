#pragma once
class LightEffect :public UI
{
protected:
	static shared_ptr<const Frame>& GetLightEffectFrame();
	static int& GetLightEffectUseCnt();

public:
	LightEffect();
	~LightEffect();

	// UI을(를) 통해 상속됨
	virtual void Update() override;
	virtual void Render() override;
	virtual void SetState(UI::UI_STATE state);
	virtual void SetID(UI::UI_ID id);
	void SetDist(float dist) { this->dist = dist; }
	void SetScale(Vector2 _scale);

	virtual void InitFrame() override;
	virtual void ClearFrame() override;

protected:
	float dist;
};