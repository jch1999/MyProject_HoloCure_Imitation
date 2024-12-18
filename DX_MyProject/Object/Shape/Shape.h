#pragma once
class Shape
{
protected:
	vector<Vertex> verticies = {};
	// vector를 이용해 이 도형이 출력되는 데 사용할 정점을 저장

	vector<VertexUV> verticies_UV = {};

	float pos_x, pos_y;
	// 도형의 위치를 기록해둘 변수
	//ID3D11Buffer* VB;
	VertexBuffer* VB;
	// 도형 각각이 그래픽 출력에 필요한 데이터를 알아서 저장하도록,
	// 각 객체가 멤버로 버퍼를 보유

	VertexShader* VS;
	PixelShader* PS;
	// 기존(TutorialScene)에는 씬에서 셰이더를 만들어서 사용했는데
	// 앞으로는 오브젝트 하나하나마다 서로 다른 독립된 셰이더를 사용할 예정
	// 따라서, 각 오브젝트마다 셰이더를 따로 거쳐가야 할 필요가 있기 때문에
	// 그 오브젝트들이 출력할 도형(=그래픽)을 담당할 shape 클래스 측에서 이들을 멤버로 선언

	ColourBuffer* CB;
	// 픽셀 셰이더에 입력할 색을 기록해둘 색 버퍼
	// 기존엔 각 정점에 입력할 색을 정점에 직접 입력하는 식이었는데,
	// 이를 도형 자체가 색의 정보를 버퍼에 가지고 있어서 
	// 이를 버퍼째로 셰이더에 넘겨 처리하는 식으로

public:
	Shape(float x, float y);
	~Shape();

	VertexBuffer** const GetBuffer() { return &VB; }
	size_t GetVertexSize() { return verticies.size(); }

	virtual void Render() = 0;
	// 자기 자신을 출력하는 기능, 앞으로 모든 오브젝트는 자기 자신을 출력하는 기능을 가질 것
	// 특히 출력하기 위해 만들어진 클래스인 Shpae 계통은 더더욱 강제

	void SetColor(Float4 colour) // 색 버퍼에 새로운 색을 저장하는 함수
	{
		CB->data.colour = colour;
	}
};