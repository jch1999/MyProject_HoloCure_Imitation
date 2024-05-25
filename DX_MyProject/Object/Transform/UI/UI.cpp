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

	for (auto c : clips)
		delete c;
	
	for (auto u : child_list)
		delete u;
}

