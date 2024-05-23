#include "framework.h"

NewTrianlge::NewTrianlge(Vector2 p, Vector2 s, float a, Float2 size, D3D11_PRIMITIVE_TOPOLOGY type)
	:Transform(p,s,a)
{
	triangle = new SRTTriangle(size, type);
}

NewTrianlge::~NewTrianlge()
{
	delete triangle;
}

void NewTrianlge::Update(Matrix* parent)
{
	this->rot.z += M_PI / 2.0f * DELTA;
	// 이 Update 함수가 호출될 때마다 이 Transform의 rot.z의 값 = z축 기준으로의 회전도를 가산
	
	this->pos.x += (float(WIN_WIDTH) / 2.0f) * DELTA;
	if (this->pos.x > WIN_WIDTH)
		this->pos.x = 0;

	if (KEY_CON->Press(VK_UP)) // 현재 위쪽 화살표 키가 눌려져있다면
	{
		this->pos.y -= 200.0f * DELTA;
	}
	if (KEY_CON->Press(VK_DOWN)) // 현재 아래쪽 화살표 키가 눌려져있다면
	{
		this->pos.y += 200.0f * DELTA;
	}

	// 업데이트를 할 때 parent를 입력받은 내용이 존재할 경우
	if (this->parent != parent) 
		this->parent = parent;	// 그 parent가 현재 이 오브젝트의 parent와 일치하지 않으면 갱신

	WorldUpdate();	// 월드를 업데이트하여 이 오브젝트의 변동 여부를 월드 행렬에 반영
}

void NewTrianlge::Render()
{
	// WB-> Set(World); // 이 트랜스폼이 셰이더에 넘길 데이터를 월드버퍼에 세팅하는 코드
	// 이는 이미 WorldUpdate가 끝날 즈음에 실행됐으니 할 필요가 없음
	WB->SetVS(0);
	// 대신, 셰이더에 데이터를 넘기는 타이밍은 이 오브젝트가 출력되기 시작할 타이밍이므로
	// 지금 셰이더의 0번 슬롯애 월드 버퍼의 데이터를 넘김

	triangle->Render();
	// 월드 버퍼 세팅이 끝났으면 trianlge을 출력
}
