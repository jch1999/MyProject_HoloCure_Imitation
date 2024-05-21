#include "framework.h"

void Quad2::SetPixelShader(wstring file)
{
	PixelShader::GetInstance(file);
}

Quad2::Quad2(wstring file, Vector2 size, Vector2 scale, Vector2 startUV, Vector2 EndUV)
	:Transform()
{
	this->scale = scale;
	texture = Texture::Add(file);

	Vector2 half_size = size * 0.5f;
	// 입력받은 파일명을 통해 확보한 파일 이미지의 크기를 받아,
	// 그 크기의 절반 사이즈를 기록한 벡터2를 만듦

	float left = -half_size.x;
	float right = half_size.x;
	float top = -half_size.y;
	float bottom = half_size.y;
	// 입력받은 크기를 이용해서 이미지를 표기할 영역을 지정할 2개의 좌표를 여기서 정의

	vertices.emplace_back(left, top, startUV.x, startUV.y);
	vertices.emplace_back(right, top, EndUV.x, startUV.y);
	vertices.emplace_back(left, bottom, startUV.x, EndUV.y);
	vertices.emplace_back(right, bottom, EndUV.x, EndUV.y);
	// 출력에 사용할 총 4개의 정점을 만들어둠

	indices = { 0, 1, 2, 3, 2, 1 };
	// 위에서 정의된 4개의 정점을 도형을 출력할 때 어떤 순서로 사용할 것인지 정의하는 
	// 인덱스 버퍼에 들어갈 내용 - 자세한 것은 IndexBuffer 클래스를 만들면서 설명

	Create();
}

Quad2::~Quad2()
{
	delete VB;
	delete IB;
	delete CB;
	delete WB;
}

void Quad2::Render()
{
	if (!is_active) return;

	WB->Set(world);
	WB->SetVS(0);
	CB->SetPS(0);

	VB->Set(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	IB->Set();

	texture->Set();

	VS->Set();
	PS->Set();

	DVC->DrawIndexed(indices.size(), 0, 0);
}

void Quad2::Create()
{
	VS = VertexShader::GetInstance(L"Shader/VertexShader/VertexUV.hlsl", 1);
	PS = PixelShader::GetInstance(L"Shader/PixelShader/PixelUV.hlsl");

	VB = new VertexBuffer(vertices.data(), sizeof(VertexUV), vertices.size());
	IB = new IndexBuffer(indices.data(), indices.size());

	CB = new ColourBuffer();
	WB = new MatrixBuffer();
}
