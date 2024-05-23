#include "framework.h"

Missile::Missile(Vector2 pos, Vector2 size, Float2 s, float a, Transform* target)
	:Quad(L"Textures/Images/arrow.png")
	,target(target)
{
	this->pos = pos;
	this->scale = s;
	this->size = size;
	this->rot.z = a * M_PI / 180;
	this->SetParent(parent);

	collider = new RectCollider(size);
	collider->pos = this->pos;
	//collider->SetParent(this->GetWorld());

	speed = 100.f;
	sleep_time = 0.f;
}

Missile::~Missile()
{
}

void Missile::Update()
{
	if (!is_active && sleep_time != 0.0f)
	{
		sleep_time -= DELTA;

		if (sleep_time <= 0.0f)
		{
			sleep_time = 0.0f;
			is_active = true;
			collider->is_active = true;


			std::random_device rd; 
			std::mt19937_64 gen(rd());
			std::uniform_real_distribution<float> init_pos_x(0.f, WIN_WIDTH);
			std::uniform_real_distribution<float> init_pos_y(0.f, WIN_HEIGHT);

			pos = Vector2(init_pos_x(gen), init_pos_y(gen));
			collider->pos = pos;

			this->WorldUpdate();
			collider->WorldUpdate();
		}
		return;
	}

	// 우리가 입력한 사이즈에 맞게 이미지의 크기를 변경하고자 할 경우
	// -> 최종적으로, 우리가 출력하고 싶은 이미지의 크기(=size)가 
	// 이미지의 크기에 scale을 곱한 값이 되도록 하면 됨
	// 그렇다는 것은, 역으로 scale의 값을 우리가 사용하는 이미지의 크기에 맞춰
	// 역산하여 저장해두고 월드 업데이트에 이용하면 된다는 것
	scale = size / texture->GetSize();
	// 이미지 파일의 크기 자체는 우리가 Texture 클래스에서 GetSize()를 통해 얻도록 구현한 바 있음
	// 그리고 그 texture를 지금 우리가 Quad를 통해 사용하고 있으므로
	// 그 함수를 가져와서 여기서 Scale을 역산하는 데 사용
	
	// 그렇게 계산된 값이 여전히 실제 충돌판정에 비해서는 약간 작은 느낌이 있으므로
	// 실제 충돌판정에 맞게 연산

	scale.y *= 1.1f;
	scale.x *= 1.1f;;

	if (target != NULL)
	{
		Vector2 dir = (target->pos - this->pos);//.Normalized();
		dir.Normalize();

		float angle = dir.Angle() + M_PI / 2.f;
		// 구한 방향백터의 각도를 위 함수를 통해 계산
		// 기본적으로 DX는 X축의 양의 방향(=오른쪽 방향)을 0으로 취급하기 때문에,
		// 만약 사용하는 이미지가 위를 바라보는 방향으로 만들어진 이미지라면
		// 0도를 가리켜야 하는 상황일 경우엔 90도를 꺾어서 오른쪽을 보도록 추가적으로 보정해줘야 함
		rot.z = angle;
		collider->rot.z = angle;

		pos += dir * speed * DELTA;
	}
	WorldUpdate();

	collider->pos = this->pos;

	// 어지간한 경우, 우리가 원하는 충돌판정의 크기와 이미지 파일의 크기는 일치하지 않는 경우가 많음
	// 때문에 보이는 것과 실제 충돌판정을 일치시키려면 적어도 둘 중 하나의 크기는 조절해야 함

	// 1) 충돌판정의 크기를 이미지에 맞게 직접 조정하는 방식
	// 정확히는 처음 생성자에서 충돌판정의 크기를 size를 통해 입력할 때
	// 이 입력값 자체를 직접 적당한 값으로 조각하는 법
	// 직관적으로 매우 간단하나, 사용하는 이미지 각각에 맞게 직접 조절해줘야 하므로 작업량이 많음

	// 2) 이미지 파일 자체의 크기를 우리가 원하는 크기로 줄인다
	// 이 방법은 코드 외적인 방식으로 크기를 조정해야 하나 어떤 의미에선 알아야 하는 지식이 더 많고,
	// 결국 최종적으로는 이미지에 맞춰서 값을 깎아야 한다는 점은 똑같음

	// 3) 이미지를 담당하는 인스턴스의 스케일 자체를 우리가 원하는 사이즈에 맞춰 조절하는 것으로
	// 충돌판정과 이미지 사이의 크기 차이를 줄인다.
	// 이미지 파일 원본을 손대지 않고 프로그램 내에서만 그 크기를 조절하여,
	// 작업량을 최대한 줄인 채로 최종 사이즈를 알맞게 조절할 수 있음

	// 물론 이렇게 했더라도 이미지 크기에 비해 충돌판정이 약간 더 클 수 있다
	// 이런 경우 때문에라도 결국 이 쪽에서도 사용하는 오브젝트마다 다르게 값을 변형시켜줘야 함
	// 그나마 이 쪽은 최종적으로 구한 scale에 적당한 값을 곱해주는 것으로 조절할 수 있으니
	// 위 방법들에 비해선 그나마 손이 덜 감

	// + 이 방식(3번)은 이미지를 사용하는 충돌판정에서만 제대로 사용 가능한 방법
	// 만약 이미지를 추가로 만든다거나 하지 않는 이펙트나 동작 등에서 충돌판정을 만들어내느 경우 등엔
	// 이 방법은 못쓰고 충돌판정 그 자체를 새로이 만들어내거나 하는 식으로 일일이 지정해줘야 함

	collider->WorldUpdate();

}

void Missile::Render()
{
	((Quad*)this)->Render(); 
	// 자식 클래스에서 부모 클래스와 같은 이름의 함수를 만들었을 경우
	// 이후 해당 함수를 호출하면 자식 클래스의 그 함수를 호출하게 되므로,
	// 부모 클래스에서 사용했었던 내용을 이용하고자 한다면
	// 위와 같이 자기 자신을 부모 클래스로서 형변환한 후에 이용할 필요가 있음

	// 이런 방식으로 코드를 이용하려면 해당 함수가 가상 함수로서 만들어져선 안 됨
	// 가상 함수로 만들어질 경우엔 기존 클래스의 함수가 호출됐을 때도 자식 클래스에서 정의된 내용이 
	// 호출될 수 있음
	// (사실 이런 걸 고려하면 Quad를 상속받아서 만들지 않는 게 안전할 수 있음)
	collider->Render();
	
}

void Missile::PostRender()
{
	ImGui::SliderFloat2("Missile's pos", (float*)&pos, 0, WIN_WIDTH);
}

bool Missile::isHit(RectCollider* object)
// 이 미사일이 다른 충돌판정 있는 오브젝트와 충돌했는가 체크하는 함수
{
	if (collider->isCollision(object))
	{
		sleep_time = 1.0f;
		is_active = false;
		collider->is_active = false;

		return true;
	}
	return false;
}
