#include "framework.h"

bool Collider::debug_mode = true;

Collider::Collider()
{
	is_active = false;
	

	VS = VertexShader::GetInstance(L"Shader/VertexShader/VertexPos.hlsl", 2);
	PS = PixelShader::GetInstance(L"Shader/PixelShader/PixelPos.hlsl");

	CB = new ColourBuffer();
	CB->data.colour = { 0,1,0,1 };

	WB = new MatrixBuffer();

}

Collider::~Collider()
{
	delete CB;
	delete WB;
}

void Collider::Render()
// 이 클래스는 순수 사상함수가 있는 추상 클래스이므로,
// 이 클래스 자체의 인스턴스가 존재할 수 없음
// -> 정점이 정의되어 정상적으로 등록된 자식 클래스에서만 이 함수가 호출될 일이 있다는 것이므로
// 이 클래스 내부에서 등록되지 않았을 맴버를 이용해도 문제가 없음
{
	if (!is_active||!debug_mode) return;
	// 이 출돌판정이 활성화되어있지 않다면 이 충돌판정을 화면에 출력하지 않음

	WB->Set(world);
	WB->SetVS(0);
	CB->SetPS(0);

	VB->Set(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);
	// 정점들으로 선만 그려서 출력하도록 함
	VS->Set();
	PS->Set();
	DVC->Draw(verticies.size(), 0);
}
 
bool Collider::isCollision(Collider* collider, Vector2* overwrap)
{
	if (collider == nullptr)return false;

	if(!is_active || !(collider->is_active)) return false;
	// 이 충돌판정이 활성화된 상태가 아니면 애초에 충돌할 일이 없음

	switch (collider->type)
	// collider는 최소 2종류 이상의 자식 클래스를 가진 추상 클래스
	// 따라서 자식 클래스 각각에 따라 사용해야 할 충돌 매커니즘이 다르기 때문에,
	// 분기문을 통해서 이를 분리
	{
	case TYPE::RECT:
		return isRectCollision((RectCollider*)collider, overwrap);
	case TYPE::CIRCLE:
		return isCircleCollision((CircleCollider*)collider);
	default:
		return false;
	}
}

bool Collider::isLineCrossCollision(Vector2 l1_start, Vector2 l1_end, 
	Vector2 l2_start, Vector2 l2_end)
// 이름 그대로 "두 개의 선분이 충돌하는지"를 검사하는 함수
// 이건 충돌판정 = 충돌하는 영역이 겹쳤는지가 아니라 단순히 두 선의 충돌여부만을 검사하는 것이므로
// 지금 이 클래스가 다루는 사각형 혹은 원형의 충돌판정 그 자체를 다루는 인스턴스를 요구하지 않음
// 따라서 인스턴스 없이도 비교가 가능한 static 함수로서 선언한 것

// 그러나 지금은 실제로 오브젝트가 가지고 있는 충돌판정 쪽을 이요하는 것을 선행하고자 하기에,
// 이 쪽은 선언만 해두고 실제 구현은 다음 이 시간에
{
	return false;
}
