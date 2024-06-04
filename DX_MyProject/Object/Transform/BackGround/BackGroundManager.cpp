#include "framework.h"

BackGroundManager::BackGroundManager()
	:player(nullptr),now_time(0.0f)
{
	// 이 방식은 tile이 900개다...256,256으로 크기를 변경하면 225개이긴 한데 랜더해야 할 사이즈가 커지니 부하 자체는 비슷한가?
	// 크기를 늘려?
	// player이동에 따라 tile의 위치를 수정하는 식을 짜야 하는데...
	Vector2 initPos(-1280.0f, -1280.0f);
	for (int a = 0; a < 3; a++) // 4중? 5중 for문 에반데?
	{
		for (int b = 0; b < 3; b++)
		{
			for (int i = 0; i < 10; i++)
			{
				for (int j = 0; j < 10; j++)
				{
					Tile* t = new Tile(i * 10 + j);
					t->pos = Vector2(initPos.x + 1280.0f * a + i * 128.0f, initPos.y + 1280.0f * b + j * 128.0f);
					if ((i == 2) && (j == 3 || j == 7) )
					{
						Tree* tree = new Tree();
						tree->SetTarget(t);
						trees.push_back(tree);

						for (int k = 0; k < 3; k++)
						{
							Flower* f = new Flower();
							f->SetTarget(t);
							f->SetOffset(Vector2(-40.0f + 40.0f * k, 100.0f));
							flowers.push_back(f);
						}
					}
					else if (((i == 0 || i == 3) || (i == 5 || i == 7)) && ((j == 0 || j == 2) || (j == 5 || j == 8)))
					{
						for (int k = 0; k < 3; k++)
						{
							Flower* f = new Flower();
							f->SetTarget(t);
							f->SetOffset(Vector2(-40.0f + 40.0f * k, 100.0f));
							flowers.push_back(f);
						}
					}
					else// if((i==3||i==9)&&((j==1||j==5)||j==8))
					{
						for (int k = 0; k<3; k++)
						{
							for (int l = 0; l < 2; l++)
							{
								Grass* g = new Grass();
								g->SetTarget(t);
								g->SetOffset(Vector2(k * 40.0f, 60.0f + l * 60.0f));
								grasses.push_back(g);
							}
						}
					}
					t->SetActive(true);
					tiles.push_back(t);
				}
			}
		}
	}
	
	for (int i = 0; i < 2; i++)
	{
		SunLight* light = new SunLight();
		light->SetTarget(CAM);
		light->SetOffset(WIN_CENTER);
		light->SetIndex(i);
		light->SetActive(true);
		lights.push_back(light);
	}
}

BackGroundManager::~BackGroundManager()
{
	for (auto t : tiles)
		delete t;
	for (auto t : trees)
		delete t;
	for (auto f : flowers)
		delete f;
	for (auto g : grasses)
		delete g;
	for (auto l : lights)
		delete l;
}

void BackGroundManager::Update()
{
	now_time += DELTA;
	if (now_time > 0.2f)
	{
		now_time -= 0.2f;
		FixedUpdate();
	}
	lights[0]->Update();
	for (auto t : trees)
	{
		if ((player->pos - t->pos).GetLength() < Vector2(128.0f, 128.0f).GetLength())
		{
			Vector2 obstacle_area;
			if (player->GetDamageCollider()->isCollision(t->GetCollider(), &obstacle_area))
			{

				Vector2 player_pos = player->GetDamageCollider()->pos;
				Vector2 obstacle_pos = t->GetCollider()->pos;

				if (obstacle_area.x > obstacle_area.y)
				{
					if (player_pos.y > obstacle_pos.y)
					{
						player->pos.y += obstacle_area.y;
					}
					else
					{
						player->pos.y -= obstacle_area.y;
					}
				}
				else
				{
					if (player_pos.x > obstacle_pos.x)
					{
						player->pos.x += obstacle_area.x;
					}
					else
					{
						player->pos.x -= obstacle_area.x;
					}
				}
			}
		}
	}
}

void BackGroundManager::FixedUpdate()
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
		else if (x == -1)
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

	for (auto t : trees)
	{
		t->Update();
	}
	for (auto f : flowers)
	{
		f->Update();
	}
	for (auto g : grasses)
	{
		g->Update();
	}
	lights[1]->Update();
}

void BackGroundManager::BeforeRender()
{
	for (auto t : tiles)
	{
		if ((t->pos - player->pos).GetLength() < Vector2(WIN_WIDTH, WIN_HEIGHT).GetLength())
			t->Render();
	}
}

void BackGroundManager::Render()
{
	
	for (auto t : trees)
	{
		if ((t->pos - player->pos).GetLength() < Vector2(WIN_WIDTH, WIN_HEIGHT).GetLength())
		{
			if (t->pos.y + 30.0f < player->pos.y)
			{
				t->SetColor(Float4(1.0f, 1.0f, 1.0f, 1.0f));
				t->Render();
			}
		}
	}
	for (auto f : flowers)
	{
		if ((f->pos - player->pos).GetLength() < Vector2(WIN_WIDTH, WIN_HEIGHT).GetLength())
		{
			if (f->pos.y< player->pos.y)
			{
				f->SetColor(Float4(1.0f, 1.0f, 1.0f, 1.0f));
				f->Render();
			}
		}
	}
	for (auto g : grasses)
	{
		if ((g->pos - player->pos).GetLength() < Vector2(WIN_WIDTH, WIN_HEIGHT).GetLength())
		{
			g->Render();
		}
	}
}

void BackGroundManager::AfterRender()
{
	for (auto t : trees)
	{
		if ((t->pos - player->pos).GetLength() < Vector2(WIN_WIDTH, WIN_HEIGHT).GetLength())
		{
			if (t->pos.y+30.0f > player->pos.y)
			{
				if(t->pos.y-player->pos.y>50.0f)
					t->SetColor(Float4(1.0f, 1.0f, 1.0f, 1.0f));
				else
					t->SetColor(Float4(1.0f, 1.0f, 1.0f, 0.85f));
				t->Render();
			}
		}
	}
	for (auto f : flowers)
	{
		if ((f->pos - player->pos).GetLength() < Vector2(WIN_WIDTH, WIN_HEIGHT).GetLength())
		{
			if (f->pos.y > player->pos.y)
			{
				if (f->pos.y - player->pos.y > 5.0f)
					f->SetColor(Float4(1.0f, 1.0f, 1.0f, 1.0f));
				else
					f->SetColor(Float4(1.0f, 1.0f, 1.0f, 0.85f));
				f->Render();
			}
		}
	}
	for (auto l : lights)
	{
		l->Render();
	}
}

void BackGroundManager::PostRneder()
{
	for (auto t : tiles)
	{
		if ((t->pos - player->pos).GetLength() < Vector2(WIN_WIDTH, WIN_HEIGHT).GetLength())
			t->PostRender();
	}
}

void BackGroundManager::SetPlayer(Player* p)
{
	this->player = p;
}
