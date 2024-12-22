#pragma once
class LightEffect :public UI
{
protected:
	shared_ptr<const Frame> lightEffectFrame;
	vector<shared_ptr<ImageArea>> lightEffect;
	float dist;
public:
	LightEffect();
	~LightEffect();

	// UI��(��) ���� ��ӵ�
	virtual void Update() override;
	virtual void Render() override;
	virtual void SetState(UI::UI_STATE state);
	virtual void SetID(UI::UI_ID id);
	void SetDist(float dist) { this->dist = dist; }
	void SetScale(Vector2 _scale);

	virtual void InitFrame() override;
	virtual void ClearFrame() override;
};