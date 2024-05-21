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
	// �Է¹��� ���ϸ��� ���� Ȯ���� ���� �̹����� ũ�⸦ �޾�,
	// �� ũ���� ���� ����� ����� ����2�� ����

	float left = -half_size.x;
	float right = half_size.x;
	float top = -half_size.y;
	float bottom = half_size.y;
	// �Է¹��� ũ�⸦ �̿��ؼ� �̹����� ǥ���� ������ ������ 2���� ��ǥ�� ���⼭ ����

	vertices.emplace_back(left, top, startUV.x, startUV.y);
	vertices.emplace_back(right, top, EndUV.x, startUV.y);
	vertices.emplace_back(left, bottom, startUV.x, EndUV.y);
	vertices.emplace_back(right, bottom, EndUV.x, EndUV.y);
	// ��¿� ����� �� 4���� ������ ������

	indices = { 0, 1, 2, 3, 2, 1 };
	// ������ ���ǵ� 4���� ������ ������ ����� �� � ������ ����� ������ �����ϴ� 
	// �ε��� ���ۿ� �� ���� - �ڼ��� ���� IndexBuffer Ŭ������ ����鼭 ����

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
