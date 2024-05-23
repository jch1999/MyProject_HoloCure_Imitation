#include "framework.h"

Circle::Circle(float radius, D3D11_PRIMITIVE_TOPOLOGY type)
	:Shape(0,0), type(type)
{
	float vertex_count = 30;
	float angle = (M_PI * 2) / vertex_count;
	vector<Vertex> circle_vertex;

	// 원의 꼭짓점들의 위치를 계산
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
			// 30개의 삼각형을 만들기 위한 정점 값들을 입력
			for (int i = 0; i < 30; i++)
			{
				if (i == 15) // 회전 여부를 확인하기 위해 삼각형 하나 제거
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
	// 도형 출력에 필요한 셰이더들과 버퍼들을 세팅
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
