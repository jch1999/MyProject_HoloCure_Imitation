#pragma once
class SRTCircle_ver_Instructor : public Shape
{
private:
	D3D11_PRIMITIVE_TOPOLOGY type;
	Float2 size;
	// 만약 타원형을 만들고 싶다면 API에서 다뤘던 것처럼 좌우/상하를 동시에 이용해야 했음
	// 여기서는 반지름만 이용하는 스타일로 만들 예정

public:
	SRTCircle_ver_Instructor(Float2 size, int vertex_count, D3D11_PRIMITIVE_TOPOLOGY type);
	SRTCircle_ver_Instructor(float radius, int vertex_count, D3D11_PRIMITIVE_TOPOLOGY type);

	~SRTCircle_ver_Instructor();


	D3D11_PRIMITIVE_TOPOLOGY GetType() { return type; }
	void Render();

};