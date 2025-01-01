#pragma once
class HPBar :public UI
{
protected:
	static vector<shared_ptr<const Frame>>& GetHPBarFrames();
	static int& GetHPBarUseCnt();

public:
	HPBar(Vector2 inSize = Vector2(40.0f, 5.0f), Vector2 inScale = Vector2(1.0f, 1.0f), Vector2 inOffset = Vector2(0.0f, 0.0f));
	~HPBar();


	// UI을(를) 통해 상속됨
	virtual void Update() override;

	virtual void Render() override;

	virtual void InitFrame() override;
	virtual void ClearFrame() override;

	virtual void SetID(UI::UI_ID id) override;
	void SetHpRate(float rate);
	void SetConstant(bool isConstant) { this->isConstant = isConstant; }

protected:
	float hpRate;
	bool isConstant;
};