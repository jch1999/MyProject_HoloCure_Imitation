#include "framework.h"

UI::UI()
{
	VS = VertexShader::GetInstance(L"Shader/VertexShader/VertexUV.hlsl", 1);
	PS = PixelShader::GetInstance(L"Shader/PixelShader/PixelUV.hlsl");
	CB = new ColourBuffer();

}

UI::~UI()
{
	delete CB;

	clips.clear();
	
	for (auto u : childList)
		delete u;
}

void UI::SetTarget(Transform* target)
{
	this->target = target;
}

void UI::SetSize(Vector2 inSize)
{
	this->uiSize = inSize;
}

void UI::SetScale(Vector2 inScale)
{
	this->uiScale = inScale;
}

void UI::SetAddtionalScale(Vector2 inScale)
{
	this->additionalScale = inScale;
}

void UI::SetOffset(Vector2 inOffset)
{
	this->offset = offset;
}

void UI::AddOffset(Vector2 inOffset)
{
	this->offset = this->offset + inOffset;
}

void UI::SetActive(bool inActive)
{
	is_active = inActive;
}

void UI::SetClipIdx(int inIdx) 
{ 
	clipIdx = inIdx; 
}

void UI::SetColor(Float4 inColor) 
{
	CB->data.colour = inColor; 
}