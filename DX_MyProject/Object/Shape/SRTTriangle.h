#pragma once
class SRTTriangle :public Shape
	// Trnasform을 이용해서 SRT 변환 행렬을 적용시킨 도형을 담당하는 클래스
{
private:
	D3D11_PRIMITIVE_TOPOLOGY type;
	Float2 size;

public:
	SRTTriangle(Float2 size,
		D3D11_PRIMITIVE_TOPOLOGY type = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	~SRTTriangle();

	D3D11_PRIMITIVE_TOPOLOGY GetType() { return type; }
	virtual void Render() override;
};