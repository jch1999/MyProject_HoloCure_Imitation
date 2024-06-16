#include "framework.h"

ImageArea::ImageArea(Frame* f)
	:frame(f)
{
	id = UI::UI_ID::IMAGE;
	type = UI::UI_TYPE::IMAGE;
	state = UI::UI_STATE::IDLE;
	ui_size = Vector2(43.0f, 38.0f);
	ui_scale = Vector2(1, 1);
	additional_scale = Vector2(1, 1);
	offset = Vector2(0, 0);
	is_active = true;
}

ImageArea::~ImageArea()
{
	delete frame;
}

void ImageArea::Update()
{
	if (!is_active)return;

	scale = frame->GetFrameSize() * ui_size / frame->GetFrameOriginSize() * ui_scale;

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

void ImageArea::PostRender()
{
	
}

void ImageArea::SetState(UI::UI_STATE state)
{
	this->state = state;
}

void ImageArea::SetID(UI::UI_ID id)
{
	this->id = id;
}
