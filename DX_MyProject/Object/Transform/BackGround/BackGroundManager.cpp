#include "framework.h"

BackGroundManager::BackGroundManager()
	:player(nullptr)
{
	// 이 방식은 tile이 900개다...256,256으로 크기를 변경하면 225개이긴 한데 랜더해야 할 사이즈가 커지니 부하 자체는 비슷한가?
	// 크기를 늘려?
	// player이동에 따라 tile의 위치를 수정하는 식을 짜야 하는데...
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
	int x = round(move_dir.x);
	int y = round(move_dir.y);
	for (auto t : tiles)
	{
		if (x == 1)
		{
			if (t->pos.x - player->pos.x < -1920.0f)
			{
				t->pos = Vector2(t->pos.x + 3840.0f, t->pos.y);
			}
		}
		else if(x==-1)
		{
			if (t->pos.x - player->pos.x > 1920.0f)
			{
				t->pos = Vector2(t->pos.x - 3840.0f, t->pos.y);
			}
		}
		if (y == 1)
		{
			if (t->pos.y - player->pos.y < -1920.0f)
			{
				t->pos = Vector2(t->pos.x, t->pos.y + 3840.0f);
			}
		}
		else if (y == -1)
		{
			if (t->pos.y - player->pos.y > 1920.0f)
			{
				t->pos = Vector2(t->pos.x, t->pos.y - 3840.0f);
			}
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
	{
		if((t->pos-player->pos).GetLength()<Vector2(WIN_WIDTH,WIN_HEIGHT).GetLength())
			t->Render();
	}
}

void BackGroundManager::PostRneder()
{
}

void BackGroundManager::SetPlayer(Player* p)
{
	this->player = p;
}
