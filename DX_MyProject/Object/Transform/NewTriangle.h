#pragma once
class NewTrianlge : public Transform
{
private:
	SRTTriangle* triangle;

public:
	NewTrianlge(Vector2 p, Vector2 s, float a, Float2 size,
		D3D11_PRIMITIVE_TOPOLOGY type = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	~NewTrianlge();

	void Update(Matrix* parent = NULL);
	void Render();

	void SetColor(Float4 colour)
	{
		triangle->SetColor(colour);
	}
};