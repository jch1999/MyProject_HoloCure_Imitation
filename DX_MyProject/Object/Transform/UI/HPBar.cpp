#include "framework.h"

HPBar::HPBar()
	:size(1.0f,1.0f)
{
	wstring file = L"Textures/UI/PC Computer - HoloCure - Save the Fans - Game Menus and HUDs.png";
	frame = new Frame(file, -4, 484, 129, 6);
}

HPBar::~HPBar()
{
	delete frame;
}

void HPBar::Update()
{
	scale = frame->GetFrameSize() * Vector2(64,64) / frame->GetFrameOriginSize() * size;
	WorldUpdate();
}

void HPBar::Render()
{
	frame->Render();
}

void HPBar::PostRender()
{
}

void HPBar::Respawn()
{
}
