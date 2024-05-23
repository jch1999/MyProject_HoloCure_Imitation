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
	if (KEY_CON->Press('R')) // R 키가 눌려있다면 원 회전
	{
		this->rot.z += r_speed * ((is_clockWise) ? 1.0f : -1.0f) * DELTA;
	}
	if (KEY_CON->Down('Q')) // Q 키가 눌려있다면 회전 방향 전환 - 시계 방향
	{
		is_clockWise = true;
	}
	if (KEY_CON->Down('E')) // E 키가 눌려있다면 회전 방향 전환 - 반시계 방향
	{
		is_clockWise = false;
	}
	
	if (KEY_CON->Press(VK_UP)) // 현재 위쪽 화살표 키가 눌려져있다면 위로 이동
	{
		this->pos.y -= 200.0f * DELTA;
	}
	if (KEY_CON->Press(VK_DOWN)) // 현재 아래쪽 화살표 키가 눌려져있다면 아래로 이동
	{
		this->pos.y += 200.0f * DELTA;
	}
	if (KEY_CON->Press(VK_RIGHT)) // 현재 오른쪽 화살표 키가 눌려져있다면 오른쪽으로 이동
	{
		this->pos.x += 200.0f * DELTA;
	}
	if (KEY_CON->Press(VK_LEFT)) // 현재 왼쪽 화살표 키가 눌려져있다면 왼쪽으로 이동
	{
		this->pos.x -= 200.0f * DELTA;
	}

	// 업데이트를 할 때 parent를 입력받은 내용이 존재할 경우
	if (this->parent != parent)
		this->parent = parent;	// 그 parent가 현재 이 오브젝트의 parent와 일치하지 않으면 갱신

	WorldUpdate();	// 월드를 업데이트하여 이 오브젝트의 변동 여부를 월드 행렬에 반영
}

void SRTCircle::Render()
{
	WB->SetVS(0);

	circle->Render();
}
