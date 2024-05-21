#include "framework.h"

RectUV::RectUV(Vector2 size, Vector2 StartUV, Vector2 EndUV, D3D11_PRIMITIVE_TOPOLOGY type)
	:Shape(0,0),type(type)
{
	Float2 half_size = Float2(size.x / 2.0f, size.y / 2.0f);
	// 이 도형의 크기로 입력받은 값을 절반으로 쪼갠 뒤,
	// 이를 정점의 위치를 정의하기 위한 값으로서 사용
	Float2& hf = half_size;
	// 레퍼런스 기능을 이용해서 half_size에 hf라는 짧은 별명을 붙여줌

	verticies_UV.emplace_back(-hf.x, -hf.y, StartUV.x, StartUV.y);
	verticies_UV.emplace_back(+hf.x, -hf.y, EndUV.x, StartUV.y);
	verticies_UV.emplace_back(-hf.x, +hf.y, StartUV.x, EndUV.y);
	verticies_UV.emplace_back(-hf.x, +hf.y, StartUV.x, EndUV.y);
	verticies_UV.emplace_back(+hf.x, -hf.y, EndUV.x, StartUV.y);
	verticies_UV.emplace_back(+hf.x, +hf.y, EndUV.x, EndUV.y);

	VS = new VertexShader(L"Shader/VertexShader/VertexUV.hlsl", 1);
	PS = new PixelShader(L"Shader/PixelShader/PixelUV.hlsl");

	VB = new VertexBuffer(verticies_UV.data(), sizeof(VertexUV), verticies_UV.size());
	CB = new ColourBuffer();
}

RectUV::~RectUV()
{
	delete VS;
	delete PS;
	delete VB;
	delete CB;
}

void RectUV::Render()
{
	CB->SetPS(0);

	VB->Set(type);
	VS->Set();
	PS->Set();
	DVC->Draw(verticies_UV.size(), 0);
}
