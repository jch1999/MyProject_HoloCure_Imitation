#pragma once
class SRTCircle : public Transform
{
private:
	Circle* circle;
	bool is_clockWise;
	float r_speed;

public:
	SRTCircle(Vector2 p, Vector2 s, float a, bool is_clockWise = true, float r_speed = 360.f,
		D3D11_PRIMITIVE_TOPOLOGY type = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	~SRTCircle();

	void Update(Matrix* parent = NULL);
	void Render();

	void SetColor(Float4 colour)
	{
		circle->SetColor(colour);
	}
};