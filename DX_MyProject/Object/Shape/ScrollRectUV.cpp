#include "framework.h"

ScrollRectUV::ScrollRectUV(Vector2 size, Float2 scroll_speed, D3D11_PRIMITIVE_TOPOLOGY type)
	:Shape(0,0),type(type),scroll_speed(scroll_speed)
{
	Float2 half_size = Float2(size.x / 2.0f, size.y / 2.0f);
	// �� ������ ũ��� �Է¹��� ���� �������� �ɰ� ��,
	// �̸� ������ ��ġ�� �����ϱ� ���� �����μ� ���

	Float2& hf = half_size;
	// ���۷��� ����� �̿��ؼ� half_size�� hf��� ª�� ������ �ٿ���

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

	// ������ ������ ��ü�� �ű�� ������� �����ߴµ�,
	// �̴� ���ȭ���� ����ϱ� ���� ���� Ʈ������ ���� ��ǥ�� �̻��� �����
	// �ǵ����� ���� ��ġ�� ������ ǥ��� ��ġ�� ����� ������ �׷��� ��õ�� �� �ִ� ����� �ƴ�
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
