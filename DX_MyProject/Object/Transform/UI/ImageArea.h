#pragma once
class ImageArea :public UI
{
protected:
	shared_ptr<const Frame> frame;

public:
	ImageArea(shared_ptr<const Frame> inFrame, Vector2 inSize=Vector2(43.0f,38.0f),Vector2 inScale=Vector2(1.0f,1.0f), Vector2 inOffset=Vector2(0.0f,0.0f));
	virtual ~ImageArea();

	// UI을(를) 통해 상속됨
	virtual void Update() override;
	virtual void Render() override;
	virtual void SetID(UI::UI_ID id);
};