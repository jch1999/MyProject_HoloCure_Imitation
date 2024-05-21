#include "framework.h"

CollisionScene::CollisionScene()
{
	player = new RectCollider(Vector2(200, 200));
	player->pos = Vector2(0, 0);
	player->is_active = true;

	obstacle = new RectCollider(Vector2(100, 400));
	obstacle->pos = Vector2(WIN_CENTER_X, WIN_CENTER_Y);
	obstacle->is_active = true;

	circle = new CircleCollider(200.0f);
	circle->pos = Vector2(WIN_CENTER_X/2.f, WIN_CENTER_Y);
	circle->is_active = true;

	m = new Missile(Vector2(WIN_CENTER_X / 2.f, WIN_CENTER_Y / 2.f), Vector2(20, 100), Vector2(1, 1), 0.0f, player);
	m->is_active = true;
	// m->GetCollider()->SetParent(m->GetWorld());
	m->GetCollider()->is_active = true;

}

CollisionScene::~CollisionScene()
{
	delete player;
	delete obstacle;
	delete circle;
}

void CollisionScene::Update()
{
	player->pos = mouse_pos;

	if (KEY_CON->Press(VK_LEFT))
	{
		player->rot.z -= M_PI / 2.0f * DELTA;
		// ������Ʈ�� ȸ������ �ٲٰ� ������
		// �̷��� Transform�� rot.z�� �ٲٸ� �ȴ�
	}
	if (KEY_CON->Press(VK_RIGHT))
	{
		player->rot.z += M_PI / 2.0f * DELTA;
	}

	if (circle->isCollision(player))
	{
		circle->SetColor(0, 0, 1);
	}
	else
	{
		circle->SetColor(0, 1, 0);
	}

	if (player->isCollision(obstacle)&& player->isCollision(circle))
	{
		player->SetColor(1, 0, 1);
	}
	else if (player->isCollision(obstacle))
	{
		player->SetColor(0, 0, 1);
	}
	else if (player->isCollision(circle))
	{
		player->SetColor(1, 1, 0);
	}
	else
	{
		player->SetColor(0, 1, 0);
	}

	if (obstacle->isPointCollision(mouse_pos))
		// ���콺�� ��ġ�� �� �浹���� ���ο� ������ ��� = �浹���� ���
	{
		obstacle->SetColor(1, 0, 0);
	}
	else if (obstacle->isCollision(player))
	{
		obstacle->SetColor(0, 0, 1);
	}
	else
	{
		obstacle->SetColor(0, 1, 0);
	}

	// ���� �浹 �߻� �� �̻��� ���� �ٸ� ��ü�� �۾��� ������ �ִٸ� 
	// �� �κ��� if������ ���� �߰������� �۾�
	m->isHit(player);

	player->WorldUpdate();
	obstacle->WorldUpdate();
	circle->WorldUpdate();
	m->Update();
}

void CollisionScene::Render()
{
	player->Render();
	obstacle->Render();
	circle->Render();
	m->Render();
}

void CollisionScene::PostRender()
{
	ImGui::SliderFloat2("Mouse's pos", (float*)&player->pos, 0, WIN_WIDTH);
	ImGui::SliderFloat2("Circle's pos", (float*)&circle->pos, 0, WIN_WIDTH);
	ImGui::SliderFloat2("Obstacle's pos", (float*)&obstacle->pos, 0, WIN_WIDTH);
	m->PostRender();
}


/*
* ���� - 2�ܰ�� ����
* 
* 1. �ٽ� �� �� �̹����� ����ϴ� ������Ʈ�� �����µ�,
* �̹����� �� ������Ʈ�� �浹������ ������ ��±��� �ǵ��� ���� ��
* 
* ���ٸ� ���� ������ ����
* �׳� ������ �̿��� ������Ʈ�� �����, ���콺 �����ӿ� �����ص� ������ �����̰� �����,
* �浹������ �ݵ�� �츮 ���� ���̵��� ���� ��
* 
* �ش� ������Ʈ�� �浹�� ���õ� ó���� �ϴ� �Լ��� ���� �ʿ�� ����
* 
* �̰� �ϳ����� ���� ���� ���� ���� �ʿ�� ����, �׳� ������Ʈ�� ������ٴ� �͸� Ȯ���� �� ������ ��
* 2�� ���� �� �ִٸ� �� �ʿ� ���Ƽ� �ص� ���� X
* 
* �̹����� ����ϴ� �ν��Ͻ��� �浹ü �ν��Ͻ��� ������ 
* ��� ������ �ð��� �����߾�� �� ���� �ð��� �����ؼ� ������ �Ѿ ��
* �浹������ ���� ��µǰ� ������ ��µ��� �ʵ��� ������ �� ��
* 
* 2. �� ������Ʈ�� �̿��ϴ� ���� �ϳ� ����,
* �ű⼭ �츮�� �������� �������� �ұ��ϰ� �ð� ����� ���� �˾Ƽ� �����̴� ������Ʈ�� �ϳ� ���� ��
* �׸���, �� ������Ʈ�� �÷��̾�� �ε����� 2�� ���� ������ٰ� 2�� �ڿ� ������ ��ġ�� ������ϵ��� ����(���� ����)
* 
* ������ ���ϸ� "���ϱ�" ������ �ϳ� ���� ��
* 
* �浹�ϴ� ������Ʈ�� �̹����� �ᵵ �ǰ� �浹������ �־ ��
* � ������ 2�� ���� ������ٰ� �ٽ� ��Ÿ���� �ϴ����� �ҹ��� ��ħ
* ���� ���̳� ������Ʈ�� ��Ȱ���ϴ��� ���� ���� ������ ����, ������ ������ ���븸 100% �ݿ��Ǿ������� �߿�
*/

/*
* ������ �ƴϰ� �غ�
* �غ� - https://www.spriters-resource.com/
* �� ����Ʈ���� ���� �ƴϾ ���������
* 
* �ѹ� ���� ������������ ĳ������ "��������Ʈ ��"�� �ϳ� ���ؿ� ��
* �̸� �̿��ؼ� ������ ���� �츮�� �ִϸ��̼��� ���� ����
*/