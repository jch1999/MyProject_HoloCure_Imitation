#include "framework.h"

SRTTriangle::SRTTriangle(Float2 size, D3D11_PRIMITIVE_TOPOLOGY type)
	:Shape(0,0),type(type)
	// Shpae의 값은 이제는 어떻게 잡아도 별 상관없음
	// 앞으로 도형의 위치 등은 Transform을 통해 관리할 것이므로 Shape가 가지고 있는 좌표의 값은
	// 더 이상 중요하지 않다
{
	Float2 half_size = Float2(size.x / 2.0f, size.y / 2.0f);
	// 이 도형의 크기로 입력받은 값을 절반으로 쪼갠 뒤,
	// 이를 정점의 위치로 정의하기 위한 값으로서 사용

	Float2& hf = half_size;
	// 레퍼런스 기능을 이용해서 half_size에 hf라는 짧은 별명을 붙여줌

	switch (type)
	{
	case D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST:
		verticies.emplace_back(0,-hf.y,1.0f,0.0f,0.0f);
		verticies.emplace_back(hf.x, hf.y, 0.0f, 1.0f, 0.0f);
		verticies.emplace_back(-hf.x, hf.y, 0.0f, 0.0f, 1.0f);
		// 기존 도형의 경우엔 "정점이 화면의 어디에 찍혀있는지"를 좌표로서 입력했음
		// 이제는 SRT변환을 이용해서 그리기 때문에,
		// 이 도형이 어디있는지는 Transform의 pos로 결정함
		// 그러므로 그 오브젝트의 그래픽을 담당하는 이 shpae는 
		// 각각의 정점들이 오브젝트이 원점을 기준으로 어디에 있는지 그 방향 백터만 제시하면 됨
		// 그게 지금 입력함 "원점에서 어느 방향으로 얼만큼 떨어져있는지"를 나타내는 백터
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

SRTTriangle::~SRTTriangle()
{
	delete VS;
	delete PS;
	delete VB;
	delete CB;
}

void SRTTriangle::Render()
{
	CB->SetPS(0);
	// 픽셀 셰이더의 0번 슬롯에 이 버퍼를 등록해 데이터를 보냄

	VB->Set(type);
	VS->Set();
	PS->Set();
	DVC->Draw(verticies.size(), 0);
}
