#include "framework.h"

ScrollRectUV::ScrollRectUV(Vector2 size, Float2 scroll_speed, D3D11_PRIMITIVE_TOPOLOGY type)
	:Shape(0,0),type(type),scroll_speed(scroll_speed)
{
	Float2 half_size = Float2(size.x / 2.0f, size.y / 2.0f);
	// 이 도형의 크기로 입력받은 값을 절반으로 쪼갠 뒤,
	// 이를 정점의 위치를 정의하기 위한 값으로서 사용

	Float2& hf = half_size;
	// 레퍼런스 기능을 이용해서 half_size에 hf라는 짧은 별명을 붙여줌

	verticies_UV.emplace_back(-hf.x, -hf.y, 0, 0);
	verticies_UV.emplace_back(+hf.x, -hf.y, 1, 0);
	verticies_UV.emplace_back(-hf.x, +hf.y, 0, 1);
	verticies_UV.emplace_back(-hf.x, +hf.y, 0, 1);
	verticies_UV.emplace_back(+hf.x, -hf.y, 1, 0);
	verticies_UV.emplace_back(+hf.x, +hf.y, 1, 1);

	VS = new VertexShader(L"Shader/VertexShader/VertexUV.hlsl", 1);
	PS = new PixelShader(L"Shader/PixelShader/PixelUV.hlsl");

	VB = new VertexBuffer(verticies_UV.data(), sizeof(VertexUV), verticies_UV.size());
	CB = new ColourBuffer();
}

ScrollRectUV::~ScrollRectUV()
{
	delete VS;
	delete PS;

	delete VB;
	delete CB;
}

void ScrollRectUV::Update()
{
	if (fabs(scroll_speed.x) < 0.0001f && fabs(scroll_speed.y) < 0.0001f)
		return;

	bool isXMinus, isXPlus, isYMinus, isYPlus;
	isXMinus = isXPlus = isYMinus = isYPlus = false;;

	for (int i = 0; i < verticies_UV.size(); i++)
	{
		if(fabs(scroll_speed.x) > 0.0001f)
			verticies_UV[i].uv.x += scroll_speed.x * DELTA;

		if (fabs(scroll_speed.y) > 0.0001f)
			verticies_UV[i].uv.y += scroll_speed.y * DELTA;

		if (verticies_UV[i].uv.x < -2.0f)
			isXMinus = true;
		else if (verticies_UV[i].uv.x > 3.0f)
			isXPlus = true;

		if (verticies_UV[i].uv.y < -2.0f)
			isYMinus = true;
		else if (verticies_UV[i].uv.y > 3.0f)
			isYPlus = true;
	}

	for (int i = 0; i < verticies_UV.size(); i++)
	{
		if (isXMinus)
			verticies_UV[i].uv.x += 2.0f;
		else if (isXPlus)
			verticies_UV[i].uv.x -= 2.0f;
		if (isYMinus)
			verticies_UV[i].uv.y += 2.0f;
		else if (isYPlus)
			verticies_UV[i].uv.y -= 2.0f;
	}

	// 정점의 데이터 자체를 옮기는 방식으로 수정했는데,
	// 이는 배경화면을 출력하기 위해 만든 트랜스폼 쪽의 좌표에 이상이 생기면
	// 의도하지 않은 위치에 정점이 표기될 위치가 생기기 때문에 그렇게 추천할 수 있는 방식은 아님
	// 

	delete VB;
	VB = new VertexBuffer(verticies_UV.data(), sizeof(VertexUV), verticies_UV.size());
}

void ScrollRectUV::Render()
{
	CB->SetPS(0);

	VB->Set(type);
	VS->Set();
	PS->Set();
	DVC->Draw(verticies_UV.size(), 0);
}
