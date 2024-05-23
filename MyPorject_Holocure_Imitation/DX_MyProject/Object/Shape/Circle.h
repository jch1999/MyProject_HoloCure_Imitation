#pragma once
class Circle : public Shape
{
private:
	D3D11_PRIMITIVE_TOPOLOGY type;
	float radius;

public:
	Circle(float radius, D3D11_PRIMITIVE_TOPOLOGY type = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	~Circle();

	D3D11_PRIMITIVE_TOPOLOGY GetType() { return type; }
	virtual void Render() override;
};