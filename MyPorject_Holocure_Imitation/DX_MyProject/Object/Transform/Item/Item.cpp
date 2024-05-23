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

	for (Clip* c : clips)
	{
		if (c != nullptr)
			delete c;
	}
}
