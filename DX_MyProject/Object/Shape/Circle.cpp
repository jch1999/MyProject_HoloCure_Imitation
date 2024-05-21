#include "framework.h"

Circle::Circle(float radius, D3D11_PRIMITIVE_TOPOLOGY type)
	:Shape(0,0), type(type)
{
	float vertex_count = 30;
	float angle = (M_PI * 2) / vertex_count;
	vector<Vertex> circle_vertex;

	// ���� ���������� ��ġ�� ���
	for (int i = 0; i < 30; i++)
	{
		circle_vertex.emplace_back(
			-cos(angle*i) * radius,
			-sin(angle*i) * radius,
			1.0f, 1.0f, 1.0f
		);
	}

	switch (type)
	{
		case D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST:
		{
			// 30���� �ﰢ���� ����� ���� ���� ������ �Է�
			for (int i = 0; i < 30; i++)
			{
				if (i == 15) // ȸ�� ���θ� Ȯ���ϱ� ���� �ﰢ�� �ϳ� ����
					continue;

				verticies.emplace_back(0, 0, 1.0f, 1.0f, 1.0f);
				verticies.emplace_back(circle_vertex[(i) % circle_vertex.size()]);
				verticies.emplace_back(circle_vertex[(i+ 1) % circle_vertex.size()]);
			}
		}
			break;
		default:
			break;
	}
	DWORD flags = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG;

	VS = new VertexShader(L"Shader/VertexShader/VertexShader.hlsl", flags);
	PS = new PixelShader(L"Shader/PixelShader/PixelShader.hlsl", flags);

	VB = new VertexBuffer(verticies.data(), sizeof(Vertex), verticies.size());
	CB = new ColourBuffer();
	// ���� ��¿� �ʿ��� ���̴���� ���۵��� ����
}

Circle::~Circle()
{
	delete VS;
	delete PS;
	delete VB;
	delete CB;
}

void Circle::Render()
{
	CB->SetPS(0);

	VB->Set(type);
	VS->Set();
	PS->Set();
	DVC->Draw(verticies.size(), 0);
}
