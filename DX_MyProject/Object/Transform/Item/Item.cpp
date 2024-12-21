#include "framework.h"

Item::Item()
{
	VS = VertexShader::GetInstance(L"Shader/VertexShader/VertexUV.hlsl", 1);
	PS = PixelShader::GetInstance(L"Shader/PixelShader/PixelUV.hlsl");
	CB = new ColourBuffer();
}

Item::~Item()
{
	//delete VS;
	//delete PS;
	//delete CB;

	for (auto& clip : clips)
	{
		clip.reset();
	}
	clips.clear();
	frame.reset();
}

void Item::SetState(ITEM_STATE inState)
{
	this->state = state;
}

void Item::SetAddtionalDir(Vector2 inDir)
{
	addtionalDir = inDir;
}
