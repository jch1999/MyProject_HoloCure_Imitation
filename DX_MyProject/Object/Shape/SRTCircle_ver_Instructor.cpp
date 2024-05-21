#include "framework.h"

SRTCircle_ver_Instructor::SRTCircle_ver_Instructor(Float2 size, int vertex_count, D3D11_PRIMITIVE_TOPOLOGY type)
	:Shape(size.x,size.y),size(size),type(type)
{
	float angle = M_PI * 2.f;

	switch (type)
	{
		case D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST:
		{
			for (int i = 0; i < vertex_count; i++)
			{
				verticies.emplace_back(0, 0, 1.0f, 1.0f, 1.0f);
				// �ﰢ���� ù��° ������ �����, �������� ������ �Է�
				verticies.emplace_back(
					-cos(angle) * this->size.x,
					sin(angle) * this->size.y,
					angle / (2 * M_PI), (2 * M_PI - angle) / (2 * M_PI), 1.0f
				);
				// �ﰢ�Լ��� ���� Ȯ���� �������� �� �� �ϳ��� �߰�

				angle -= 2 * M_PI / float(vertex_count);
				// ���� ����

				verticies.emplace_back(
					-cos(angle) * this->size.x,
					sin(angle) * this->size.y,
					angle / (2 * M_PI), (2 * M_PI - angle) / (2 * M_PI), 1.0f
				);
				// �ﰢ�Լ��� ���� Ȯ���� �������� ���� ���� �߰�
			}
		}
		break;
		case D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP:
		{
			for (int i = 0; i <= vertex_count; i++)
			{
				verticies.emplace_back(
					-cos(angle) * this->size.x,
					sin(angle) * this->size.y,
					angle / (2 * M_PI), (2 * M_PI - angle) / (2 * M_PI), 1.0f
				);
				angle -= 2 * M_PI / float(vertex_count);
			}
			// �� ���� �������� �߰��� ������� �Ѵٴ� �� ���� �������鸸 ���������� �߰��ϸ� ��

		}
		break;
	}

	DWORD flags = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG;

	VS = new VertexShader(L"Shader/VertexShader/VertexShader.hlsl", flags);
	PS = new PixelShader(L"Shader/PixelShader/PixelShader.hlsl", flags);

	VB = new VertexBuffer(verticies.data(), sizeof(Vertex), verticies.size());
	CB = new ColourBuffer();

}

SRTCircle_ver_Instructor::SRTCircle_ver_Instructor(float radius, int vertex_count, D3D11_PRIMITIVE_TOPOLOGY type)
	:SRTCircle_ver_Instructor(Float2(radius,radius),vertex_count,type)
	// ���� �����ڴ� �ڱ� �ڽ��� �ٸ� �����ڷε� �̿��� �� �ִ�
{
}

SRTCircle_ver_Instructor::~SRTCircle_ver_Instructor()
{
	delete VB;
	delete VS;
	delete PS;
	delete CB;
}

void SRTCircle_ver_Instructor::Render()
{
	//if (CB->data.colour.x != 1.0f || CB->data.colour.y != 1.0f || CB->data.colour.z != 1.0f)
		CB->SetPS(0);
	// �÷����ۿ� ����� ������ ����� �ƴ϶��
	// �� �÷����۸� ���̴��� �Է��� ��

	VB->Set(type);
	VS->Set();
	PS->Set();
	DVC->Draw(verticies.size(), 0);

}
