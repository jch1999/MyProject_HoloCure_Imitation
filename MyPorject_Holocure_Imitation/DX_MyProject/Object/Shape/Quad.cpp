#include "Framework.h"

void Quad::SetPixelShader(wstring file)
{
	PixelShader::GetInstance(file);
	// ���� ���̴��� �ߺ��ؼ� �����ϴ� ���� ���� ���ؼ�
	// �ȼ� ���̴��� �̱���� ����� �������� �ϳ��� ���� ������ �̿��Ѥ� ���̴��� �ϳ��� �����ϵ���
	// �׷� ������� ��ÿ�� �����ϴ� ������ �������� ������ ��ģ �� ����
	// ���� �� �κ��� Quad�� ������ ����, ���⼭ ����� �ȼ� ���̴��� ����(Ȥ�� �ҷ�����) �۾�
	// 
}

Quad::Quad(wstring file, Vector2 scale, Vector2 startUV, Vector2 EndUV)
	: Transform()
{
	this->scale = scale;
	texture = Texture::Add(file);

	Vector2 size = texture->GetSize();
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
	// ���� ����(Ư�� ���� ����)�� �������� ���������� ���� �Լ� �õ�

}

Quad::~Quad()
{
	delete VB;
	delete IB;
	delete CB;
	delete WB;
}

void Quad::Render()
{
	if (!is_active) return;
	// �ڱ� �ڽ��� ���� Ȱ��ȭ���� �ƴ϶�� ������� �ʰ� �Լ� ����
	// ������ �츮�� ���ӿ� ���� ������Ʈ���� ��κ� ������ �����ϱ� ���� �̸� ������ ��
	// ���� ���� ������ �̸� �����ǿ� ��ġ�ϴ� ������ �������� ������ ����
	// -> ó���� ��ġ�Ǳ� ������ ���� ���� ���ִٴ� �̾߱Ⱑ ��
	// �ٸ��� ���ϸ� ���� �΋H���� ��ȣ�ۿ��� �ϰ� ������� �ִ� ������Ʈ����
	// ������ ���۵����� �ʾҴµ� ���ʿ��ϰ� ��ȣ�ۿ��ϴ� ��찡 �Ͼ �� ����
	
	// �̸� ���� ���ؼ� �ش� ������Ʈ�� Ȱ��ȭ�Ǿ��ִ����� ���θ�
	// �÷��׸� �̿��ؼ� ����, Ȱ��ȭ�Ǿ����� �ʴٸ� ��ȭ�ۿ��� ���� �ʵ��� ���ǹ��� �����ص� ��

	WB->Set(world);
	WB->SetVS(0);
	CB->SetPS(0);

	VB->Set(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	IB->Set();

	texture->Set();

	VS->Set();
	PS->Set();

	DVC->DrawIndexed(indices.size(), 0, 0);
	// �׳� Draw�� ������ ���� ������� �տ������� �̿�������,
	// DrawIndexed�� �Է¹��� �ε��� ���ۿ� ���� ������� ������ �̿�

}

void Quad::Create()
{
	VS = VertexShader::GetInstance(L"Shader/VertexShader/VertexUV.hlsl", 1);
	PS = PixelShader::GetInstance(L"Shader/PixelShader/PixelUV.hlsl");

	VB = new VertexBuffer(vertices.data(), sizeof(VertexUV), vertices.size());
	IB = new IndexBuffer(indices.data(), indices.size());

	CB = new ColourBuffer();
	WB = new MatrixBuffer();
}