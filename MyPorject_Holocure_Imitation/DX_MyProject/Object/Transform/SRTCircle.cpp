#include "framework.h"

SRTCircle::SRTCircle(Vector2 p, Vector2 s, float a, bool is_clockWise, float r_speed, D3D11_PRIMITIVE_TOPOLOGY type)
	:Transform(p,s,a),
	is_clockWise(is_clockWise), r_speed(r_speed)
{
	circle = new Circle(50.0f, type);
}

SRTCircle::~SRTCircle()
{
	delete circle;
}

void SRTCircle::Update(Matrix* parent)
{
	if (KEY_CON->Press('R')) // R Ű�� �����ִٸ� �� ȸ��
	{
		this->rot.z += r_speed * ((is_clockWise) ? 1.0f : -1.0f) * DELTA;
	}
	if (KEY_CON->Down('Q')) // Q Ű�� �����ִٸ� ȸ�� ���� ��ȯ - �ð� ����
	{
		is_clockWise = true;
	}
	if (KEY_CON->Down('E')) // E Ű�� �����ִٸ� ȸ�� ���� ��ȯ - �ݽð� ����
	{
		is_clockWise = false;
	}
	
	if (KEY_CON->Press(VK_UP)) // ���� ���� ȭ��ǥ Ű�� �������ִٸ� ���� �̵�
	{
		this->pos.y -= 200.0f * DELTA;
	}
	if (KEY_CON->Press(VK_DOWN)) // ���� �Ʒ��� ȭ��ǥ Ű�� �������ִٸ� �Ʒ��� �̵�
	{
		this->pos.y += 200.0f * DELTA;
	}
	if (KEY_CON->Press(VK_RIGHT)) // ���� ������ ȭ��ǥ Ű�� �������ִٸ� ���������� �̵�
	{
		this->pos.x += 200.0f * DELTA;
	}
	if (KEY_CON->Press(VK_LEFT)) // ���� ���� ȭ��ǥ Ű�� �������ִٸ� �������� �̵�
	{
		this->pos.x -= 200.0f * DELTA;
	}

	// ������Ʈ�� �� �� parent�� �Է¹��� ������ ������ ���
	if (this->parent != parent)
		this->parent = parent;	// �� parent�� ���� �� ������Ʈ�� parent�� ��ġ���� ������ ����

	WorldUpdate();	// ���带 ������Ʈ�Ͽ� �� ������Ʈ�� ���� ���θ� ���� ��Ŀ� �ݿ�
}

void SRTCircle::Render()
{
	WB->SetVS(0);

	circle->Render();
}
