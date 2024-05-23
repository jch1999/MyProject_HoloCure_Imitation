#include "Framework.h"

void Quad::SetPixelShader(wstring file)
{
	PixelShader::GetInstance(file);
	// 같은 셰이더를 중복해서 생성하는 것을 막기 위해서
	// 픽셀 셰이더를 싱글톤과 비슷한 느낌으로 하나의 같은 파일을 이용한ㄴ 셰이더는 하나만 존재하도록
	// 그런 방식으로 객첼ㄹ 생성하는 디자인 패턴으로 개조를 거친 바 있음
	// 지금 이 부분은 Quad의 생성을 위해, 여기서 사용할 픽셀 셰이더를 생성(혹은 불러오는) 작업
	// 
}

Quad::Quad(wstring file, Vector2 scale, Vector2 startUV, Vector2 EndUV)
	: Transform()
{
	this->scale = scale;
	texture = Texture::Add(file);

	Vector2 size = texture->GetSize();
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
	// 사전 세팅(특히 정점 세팅)이 끝났으면 본격적으로 생성 함수 시동

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
	// 자기 자신이 현재 활성화중이 아니라면 출력하지 않고 함수 종료
	// 앞으로 우리는 게임에 사용될 오브젝트들을 대부분 게임이 시작하기 전에 미리 만들어둔 뒤
	// 게임 시작 직전에 이를 게임판에 배치하는 식으로 게임판을 구성할 예정
	// -> 처음에 배치되기 전에는 같은 곳에 모여있다는 이야기가 됨
	// 다르게 말하면 서로 부딫히면 상호작용을 하게 만들어져 있는 오브젝트들이
	// 게임이 시작되지도 않았는데 불필요하게 상호작용하는 경우가 일어날 수 있음
	
	// 이를 막기 위해서 해당 오브젝트가 활성화되어있는지의 여부를
	// 플래그를 이용해서 관리, 활성화되어있지 않다면 상화작용을 하지 않도록 조건문을 구성해둔 것

	WB->Set(world);
	WB->SetVS(0);
	CB->SetPS(0);

	VB->Set(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	IB->Set();

	texture->Set();

	VS->Set();
	PS->Set();

	DVC->DrawIndexed(indices.size(), 0, 0);
	// 그냥 Draw는 정점의 순서 상관없이 앞에서부터 이용했으나,
	// DrawIndexed는 입력받은 인덱스 버퍼에 적힌 순서대로 정점을 이용

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