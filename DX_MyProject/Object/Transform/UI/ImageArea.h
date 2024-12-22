#pragma once
class ImageArea :public UI
{
protected:
	shared_ptr<const Frame> frame;

public:
	ImageArea(shared_ptr<const Frame>& inFrame);
	virtual ~ImageArea();

	// UI을(를) 통해 상속됨
	virtual void Update() override;
	virtual void Render() override;
	virtual void SetID(UI::UI_ID id);
};