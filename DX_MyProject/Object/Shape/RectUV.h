#pragma once
class RectUV :public Shape
{
private:
	D3D11_PRIMITIVE_TOPOLOGY type;

public:
	RectUV(Vector2 size, Vector2 StartUV = Vector2(0, 0), Vector2 EndUV = Vector2(1, 1),
		D3D11_PRIMITIVE_TOPOLOGY type = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	~RectUV();

	D3D11_PRIMITIVE_TOPOLOGY GetTyoe() { return type; }
	void Render();

};