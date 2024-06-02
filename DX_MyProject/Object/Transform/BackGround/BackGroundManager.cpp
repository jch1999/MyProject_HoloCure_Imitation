#include "framework.h"

BackGroundManager::BackGroundManager()
	:player(nullptr)
{
	// �� ����� tile�� 900����...256,256���� ũ�⸦ �����ϸ� 225���̱� �ѵ� �����ؾ� �� ����� Ŀ���� ���� ��ü�� ����Ѱ�?
	// ũ�⸦ �÷�?
	// player�̵��� ���� tile�� ��ġ�� �����ϴ� ���� ¥�� �ϴµ�...
	Vector2 initPos(-1280.0f, -1280.0f);
	for (int a = 0; a < 3; a++)
	{
		for (int b = 0; b < 3; b++)
		{
			for (int i = 0; i < 10; i++)
			{
				for (int j = 0; j < 10; j++)
				{
					Tile* t = new Tile(i * 10 + j);
					t->pos = Vector2(initPos.x + 1280.0f * a + i * 128.0f, initPos.y + 1280.0f * b + j * 128.0f);
					tiles.push_back(t);
				}
			}
		}
	}
	
}

BackGroundManager::~BackGroundManager()
{
	for (auto t : tiles)
		delete t;
}

void BackGroundManager::SetPos(Tile* t)
{
}

void BackGroundManager::Update()
{
	Vector2 move_dir = player->GetMoveDir();
	for (auto t : tiles)
	{
		if (move_dir.x > 0.0f)
		{
			if(t->pos.x - player->pos.x < 1920)
				t->pos = Vector2(t->pos.x + 5120.0f, t->pos.y);
		}
		else
		{
			if (t->pos.x - player->pos.x < 2560.0f)
				t->pos = Vector2(t->pos.x + 5120.0f, t->pos.y);
		}

		if (move_dir.y > 0.0f)
		{

		}
		else
		{

		}
		t->Update();
	}
}

void BackGroundManager::FixedUpdate()
{
}

void BackGroundManager::Render()
{
	for (auto t : tiles)
		t->Render();
}

void BackGroundManager::PostRneder()
{
}

void BackGroundManager::SetPlayer(Player* p)
{
	this->player = p;
}
