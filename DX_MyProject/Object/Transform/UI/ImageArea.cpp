#include "framework.h"

ImageArea::ImageArea(shared_ptr<const Frame>& inFrame)
	:frame(inFrame)
{
	id = UI::UI_ID::IMAGE;
	type = UI::UI_TYPE::IMAGE;
	state = UI::UI_STATE::IDLE;
	uiSize = Vector2(43.0f, 38.0f);
	uiScale = Vector2(1, 1);
	additionalScale = Vector2(1, 1);
	offset = Vector2(0, 0);
	is_active = true;
}

ImageArea::~ImageArea()
{
	frame.reset();
}

void ImageArea::Update()
{
	if (!is_active)return;

	scale = frame->GetFrameSize() * uiSize / frame->GetFrameOriginSize() * uiScale;

	if(target!=nullptr)
		pos = target->pos + offset;
	
	WorldUpdate();
}

void ImageArea::Render()
{
	if (!is_active)return;

	switch (state)
	{
	case UI::UI_STATE::IDLE:
		break;
	case UI::UI_STATE::ACTIVE:
	{
		VS->Set();
		PS->Set();

		WB->SetVS(0);
		CB->SetPS(0);

		frame->Render();
	}
		break;
	default:
		break;
	}
}

void ImageArea::SetID(UI::UI_ID id)
{
	this->id = id;
}
