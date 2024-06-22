#include "framework.h"

ExitPanel::ExitPanel()
{
}

ExitPanel::~ExitPanel()
{
}

void ExitPanel::Update()
{
	if (!is_active)return;

	Panel::Update();
}

void ExitPanel::Render()
{
	if (!is_active)return;

	Panel::Render();
}

void ExitPanel::PostRender()
{
	if (!is_active)return;
	Panel::PostRender();
}

