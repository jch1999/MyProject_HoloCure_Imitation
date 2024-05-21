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

	// �츮�� �Է��� ����� �°� �̹����� ũ�⸦ �����ϰ��� �� ���
	// -> ����������, �츮�� ����ϰ� ���� �̹����� ũ��(=size)�� 
	// �̹����� ũ�⿡ scale�� ���� ���� �ǵ��� �ϸ� ��
	// �׷��ٴ� ����, ������ scale�� ���� �츮�� ����ϴ� �̹����� ũ�⿡ ����
	// �����Ͽ� �����صΰ� ���� ������Ʈ�� �̿��ϸ� �ȴٴ� ��
	scale = size / texture->GetSize();
	// �̹��� ������ ũ�� ��ü�� �츮�� Texture Ŭ�������� GetSize()�� ���� �򵵷� ������ �� ����
	// �׸��� �� texture�� ���� �츮�� Quad�� ���� ����ϰ� �����Ƿ�
	// �� �Լ��� �����ͼ� ���⼭ Scale�� �����ϴ� �� ���
	
	// �׷��� ���� ���� ������ ���� �浹������ ���ؼ��� �ణ ���� ������ �����Ƿ�
	// ���� �浹������ �°� ����

	scale.y *= 1.1f;
	scale.x *= 1.1f;;

	if (target != NULL)
	{
		Vector2 dir = (target->pos - this->pos);//.Normalized();
		dir.Normalize();

		float angle = dir.Angle() + M_PI / 2.f;
		// ���� ��������� ������ �� �Լ��� ���� ���
		// �⺻������ DX�� X���� ���� ����(=������ ����)�� 0���� ����ϱ� ������,
		// ���� ����ϴ� �̹����� ���� �ٶ󺸴� �������� ������� �̹������
		// 0���� �����Ѿ� �ϴ� ��Ȳ�� ��쿣 90���� ��� �������� ������ �߰������� ��������� ��
		rot.z = angle;
		collider->rot.z = angle;

		pos += dir * speed * DELTA;
	}
	WorldUpdate();

	collider->pos = this->pos;

	// �������� ���, �츮�� ���ϴ� �浹������ ũ��� �̹��� ������ ũ��� ��ġ���� �ʴ� ��찡 ����
	// ������ ���̴� �Ͱ� ���� �浹������ ��ġ��Ű���� ��� �� �� �ϳ��� ũ��� �����ؾ� ��

	// 1) �浹������ ũ�⸦ �̹����� �°� ���� �����ϴ� ���
	// ��Ȯ���� ó�� �����ڿ��� �浹������ ũ�⸦ size�� ���� �Է��� ��
	// �� �Է°� ��ü�� ���� ������ ������ �����ϴ� ��
	// ���������� �ſ� �����ϳ�, ����ϴ� �̹��� ������ �°� ���� ��������� �ϹǷ� �۾����� ����

	// 2) �̹��� ���� ��ü�� ũ�⸦ �츮�� ���ϴ� ũ��� ���δ�
	// �� ����� �ڵ� ������ ������� ũ�⸦ �����ؾ� �ϳ� � �ǹ̿��� �˾ƾ� �ϴ� ������ �� ����,
	// �ᱹ ���������δ� �̹����� ���缭 ���� ��ƾ� �Ѵٴ� ���� �Ȱ���

	// 3) �̹����� ����ϴ� �ν��Ͻ��� ������ ��ü�� �츮�� ���ϴ� ����� ���� �����ϴ� ������
	// �浹������ �̹��� ������ ũ�� ���̸� ���δ�.
	// �̹��� ���� ������ �մ��� �ʰ� ���α׷� �������� �� ũ�⸦ �����Ͽ�,
	// �۾����� �ִ��� ���� ä�� ���� ����� �˸°� ������ �� ����

	// ���� �̷��� �ߴ��� �̹��� ũ�⿡ ���� �浹������ �ణ �� Ŭ �� �ִ�
	// �̷� ��� �������� �ᱹ �� �ʿ����� ����ϴ� ������Ʈ���� �ٸ��� ���� ����������� ��
	// �׳��� �� ���� ���������� ���� scale�� ������ ���� �����ִ� ������ ������ �� ������
	// �� ����鿡 ���ؼ� �׳��� ���� �� ��

	// + �� ���(3��)�� �̹����� ����ϴ� �浹���������� ����� ��� ������ ���
	// ���� �̹����� �߰��� ����ٰų� ���� �ʴ� ����Ʈ�� ���� ��� �浹������ ������ ��� �
	// �� ����� ������ �浹���� �� ��ü�� ������ �����ų� �ϴ� ������ ������ ��������� ��

	collider->WorldUpdate();

}

void Missile::Render()
{
	((Quad*)this)->Render(); 
	// �ڽ� Ŭ�������� �θ� Ŭ������ ���� �̸��� �Լ��� ������� ���
	// ���� �ش� �Լ��� ȣ���ϸ� �ڽ� Ŭ������ �� �Լ��� ȣ���ϰ� �ǹǷ�,
	// �θ� Ŭ�������� ����߾��� ������ �̿��ϰ��� �Ѵٸ�
	// ���� ���� �ڱ� �ڽ��� �θ� Ŭ�����μ� ����ȯ�� �Ŀ� �̿��� �ʿ䰡 ����

	// �̷� ������� �ڵ带 �̿��Ϸ��� �ش� �Լ��� ���� �Լ��μ� ��������� �� ��
	// ���� �Լ��� ������� ��쿣 ���� Ŭ������ �Լ��� ȣ����� ���� �ڽ� Ŭ�������� ���ǵ� ������ 
	// ȣ��� �� ����
	// (��� �̷� �� ����ϸ� Quad�� ��ӹ޾Ƽ� ������ �ʴ� �� ������ �� ����)
	collider->Render();
	
}

void Missile::PostRender()
{
	ImGui::SliderFloat2("Missile's pos", (float*)&pos, 0, WIN_WIDTH);
}

bool Missile::isHit(RectCollider* object)
// �� �̻����� �ٸ� �浹���� �ִ� ������Ʈ�� �浹�ߴ°� üũ�ϴ� �Լ�
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
