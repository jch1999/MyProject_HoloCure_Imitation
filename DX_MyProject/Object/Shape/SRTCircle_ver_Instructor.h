#pragma once
class SRTCircle_ver_Instructor : public Shape
{
private:
	D3D11_PRIMITIVE_TOPOLOGY type;
	Float2 size;
	// ���� Ÿ������ ����� �ʹٸ� API���� �ٷ�� ��ó�� �¿�/���ϸ� ���ÿ� �̿��ؾ� ����
	// ���⼭�� �������� �̿��ϴ� ��Ÿ�Ϸ� ���� ����

public:
	SRTCircle_ver_Instructor(Float2 size, int vertex_count, D3D11_PRIMITIVE_TOPOLOGY type);
	SRTCircle_ver_Instructor(float radius, int vertex_count, D3D11_PRIMITIVE_TOPOLOGY type);

	~SRTCircle_ver_Instructor();


	D3D11_PRIMITIVE_TOPOLOGY GetType() { return type; }
	void Render();

};