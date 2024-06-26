#pragma once
class LightEffect :public UI
{
protected:
	vector<ImageArea*> lightEffect;
	float dist;
public:
	LightEffect();
	~LightEffect();

	// UI을(를) 통해 상속됨
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;
	virtual void SetState(UI::UI_STATE state);
	virtual void SetID(UI::UI_ID id);
	void SetDist(float dist) { this->dist = dist; }
	void SetScale(Vector2 _scale);
};