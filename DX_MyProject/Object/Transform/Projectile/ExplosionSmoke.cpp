#include "framework.h"

vector<shared_ptr<const Frame>>& ExplosionSmoke::GetExplosionSmokeFrames()
{
	static vector<shared_ptr<const Frame>> explosionSmokeFrames;
	return explosionSmokeFrames;
}

int& ExplosionSmoke::GetExplosionSmokeUseCnt()
{
	static int explosionSmokeUseCnt = 0;
	return explosionSmokeUseCnt;
}

ExplosionSmoke::ExplosionSmoke(ProjectileSize projSize)
	:Projectile(projSize, 20.0f, 200.0f, 1, 2.0f)
	, size(size)
{
	if (GetExplosionSmokeFrames().empty())
	{
		InitFrame();
	}
	
	clips.push_back(make_shared<Clip>(GetExplosionSmokeFrames(), Clip::CLIP_TYPE::END, 1 / 12.0f));
	clipIdx = 0;

	colliders.push_back(new RectCollider(size));
	colliders.push_back(new RectCollider(size*1.15f));
	colliders.push_back(new RectCollider(size*1.2f));
	collider = colliders[0];

	is_active = false;
	collider->SetActive(false);

	++GetExplosionSmokeUseCnt();
}

ExplosionSmoke::~ExplosionSmoke()
{
	if ((--GetExplosionSmokeUseCnt()) == 0)
	{
		ClearFrame();
	}
}

void ExplosionSmoke::InitFrame()
{
	auto& explosionSmokeFrames = GetExplosionSmokeFrames();
	if (!explosionSmokeFrames.empty()) return;

	wstring file = L"Textures/Skill/PC Computer - HoloCure - Save the Fans - Weapons_rm_bg.png";
	
	Vector2 initPos(4.0f, 1194.0f);
	Vector2 frameSize(128.0f, 128.0f);
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			explosionSmokeFrames.push_back(make_shared<const Frame>(file, initPos.x + j * 130.0f, initPos.y + i * 130.0f
				, frameSize.x, frameSize.y));
			if (i == 2 && j == 2)
				break;
		}
	}
}

void ExplosionSmoke::ClearFrame()
{
	GetExplosionSmokeFrames().clear();
}

void ExplosionSmoke::Update()
{
	if (!is_active)return;

	WorldUpdate();

	collider->pos = pos;
	collider->rot.z = this->rot.z;
	collider->WorldUpdate();

	scale = clips[clipIdx]->GetFrameSize() * collider->Size() /
		clips[clipIdx]->GetFrameOriginSize();

	clips[clipIdx]->Update();
	if (clips[clipIdx]->GetFrameNum() == (clips[clipIdx]->GetFrameCnt() - 1))
	{
		is_active = false;
		collider->SetActive(false);
	}
	else
	{
		OnCollision();
	}
}

void ExplosionSmoke::Render()
{
	if (!is_active)return;

	VS->Set();
	PS->Set();

	WB->SetVS(0);
	CB->SetPS(0);

	clips[clipIdx]->Render();
	collider->Render();
}

void ExplosionSmoke::respwan()
{
	WorldUpdate();
	collider->pos = pos;
	collider->WorldUpdate();
	scale = clips[clipIdx]->GetFrameSize() * collider->Size() /
		clips[clipIdx]->GetFrameOriginSize();

	hitEnemies.clear();
	enemyNowFrame.clear();

	SetActive(true);
	collider->SetActive(true);
	clips[clipIdx]->Play();
}

void ExplosionSmoke::OnCollision()
{
	pair<int, int> pPos = make_pair((int)(pos.x) / CELL_X, (int)(pos.y) / CELL_Y);
	list<Enemy*> enemyList = EnemySpawner::Get()->GetPartition(pPos);

	enemyNowFrame.clear();

	for (auto enemy : enemyList)
	{
		if (enemy->is_active)
		{
			// 面倒 贸府
			float minDist = GetCollider()->Size().GetLength() + enemy->GetDamageCollider()->Size().GetLength();
			float differDist = (enemy->pos - pos).GetLength();
			if (minDist > differDist)
			{
				if (GetCollider()->isCollision(enemy->GetDamageCollider()))
				{
					// 单固瘤 林扁
					if (hitEnemies.find(enemy) == hitEnemies.end())
					{
						hitEnemies.insert(enemy);
						bool isCrt = Owner->GetPlayer()->isCritical();
						if (isCrt)
							enemy->ChangeHP(-(GetDamage()*1.5f), isCrt);
						else
							enemy->ChangeHP(-(GetDamage()), isCrt);
						
					}
				}
			}
		}
	}
}

void ExplosionSmoke::Hit()
{
}

bool ExplosionSmoke::isDamageAble()
{
	return is_active&&(clips[clipIdx]->GetFrameNum()<clips[clipIdx]->GetFrameCnt()/5);
}
