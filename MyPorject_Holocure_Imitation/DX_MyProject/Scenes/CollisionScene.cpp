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
		// 오브젝트의 회전도를 바꾸고 싶으면
		// 이렇게 Transform의 rot.z를 바꾸면 된다
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
		// 마우스의 위치가 이 충돌판정 내부에 존재할 경우 = 충돌했을 경우
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

	// 만약 충돌 발생 시 미사일 말고도 다른 객체에 작업할 내용이 있다면 
	// 이 부분을 if문으로 만들어서 추가적으로 작업
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
* 과제 - 2단계로 진행
* 
* 1. 다시 한 번 이미지를 출력하는 오브젝트를 만들어보는데,
* 이번에는 그 오브젝트가 충돌판정을 가지고 출력까지 되도록 만들어볼 것
* 
* 별다른 제한 조건은 없음
* 그냥 사진을 이용한 오브젝트를 만들고, 마우스 움직임에 반응해도 좋으니 움직이게 만들고,
* 충돌판정이 반드시 우리 눈에 보이도록 만들 것
* 
* 해당 오브젝트가 충돌과 관련된 처리를 하는 함수를 만들 필요는 없음
* 
* 이거 하나만을 위해 씬을 새로 만들 필요는 없고, 그냥 오브젝트를 만들었다는 것만 확인할 수 있으면 됨
* 2를 만들 수 있다면 그 쪽에 몰아서 해도 문제 X
* 
* 이미지를 출력하는 인스턴스와 충돌체 인스턴스를 가지는 
* 사실 자투리 시간에 진행했어야 할 내용 시간이 부족해서 과제로 넘어간 것
* 충돌판정의 선만 출력되고 안쪽은 출력되지 않도록 만들어야 할 듯
* 
* 2. 위 오브젝트를 이용하는 씬을 하나 만들어서,
* 거기서 우리가 조작하지 않음에도 불구하고 시간 경과에 따라 알아서 움직이는 오브젝트를 하나 만들 것
* 그리고, 그 오브젝트가 플레이어와 부딪히면 2초 동안 사라졌다가 2초 뒤에 무작위 위치에 재등장하도록 구성(랜덤 스폰)
* 
* 간단히 말하면 "피하기" 게임을 하나 만들어볼 것
* 
* 충돌하는 오브젝트는 이미지를 써도 되고 충돌판정만 있어도 됨
* 어떤 식으로 2초 동안 사라졌다가 다시 나타나게 하는지는 불문에 부침
* 기존 씬이나 오브젝트를 재활용하는지 등은 전혀 따지지 않음, 위에서 설명한 내용만 100% 반영되었는지가 중요
*/

/*
* 과제는 아니고 준비물
* 준비물 - https://www.spriters-resource.com/
* 위 사이트여도 좋고 아니어도 상관없으니
* 
* 한번 직접 움직여보고픈 캐릭터의 "스프라이트 맵"을 하나 구해올 것
* 이를 이용해서 다음에 직접 우리가 애니메이션을 만들어볼 것임
*/