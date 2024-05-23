#include "framework.h"

UI::UI()
{
	VS = VertexShader::GetInstance(L"Shader/VertexShader/VertexUV.hlsl", 1);
	PS = PixelShader::GetInstance(L"Shader/PixelShader/PixelUV.hlsl");
	CB = new ColourBuffer();

	parent = target->GetWorld();
}

UI::~UI()
{
	delete CB;

	delete collider;
	for (auto c : clips)
		delete c;
	
	for (auto u : child_list)
		delete u;
}

void UI::SetTarget(Transform* target,Vector2 offset)
{
	this->target = target;
	this->offset = offset;
	parent = target->GetWorld();
	pos = offset;
}
