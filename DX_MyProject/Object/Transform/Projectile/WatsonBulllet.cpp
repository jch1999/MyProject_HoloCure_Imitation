#include "framework.h"

vector<shared_ptr<const Frame>> WatsonBullet::bulletFrames;
int WatsonBullet::bulletUseCnt = 0;

WatsonBullet::WatsonBullet(ProjectileSize projSize)
	:Projectile(projSize,20.0f, 200.0f, 1, 2.0f)
	, isRicochet(false)
	,ricochetCnt(0)
{
	if (bulletFrames.empty())
	{
		Init();
	}

	clips.push_back(make_shared<Clip>(bulletFrames, Clip::CLIP_TYPE::PINGPONG, 1.0f / 8.0f));
	clipIdx = 0;

	colliders.push_back(new RectCollider(size));
	colliders[0]->SetActive(false);
	collider = colliders[0];
	collider->pos = pos;
	
	is_active = false;

	++bulletUseCnt;
}

WatsonBullet::~WatsonBullet()
{
	if ((--bulletUseCnt) == 0)
	{
		bulletFrames.clear();
	}
}

void WatsonBullet::Init()
{
	if (!bulletFrames.empty()) return;

	wstring file = L"Textures/Player/PC Computer - HoloCure - Save the Fans - Amelia Watson_rm_bg.png";
	
	bulletFrames.push_back(make_shared<const Frame>(file, 18, 1047, 10, 8));
	bulletFrames.push_back(make_shared<const Frame>(file, 51, 1047, 10, 8));
}

void WatsonBullet::Update()
{
	if (!is_active)return;

	pos += moveDir * speed * DELTA;
	nowTime += DELTA;

	if (nowTime >= lifeTime)
	{
		is_active = false;
		nowTime = 0.0f;
	}

	WorldUpdate();

	collider->pos = pos;
	collider->rot.z = this->rot.z;
	collider->WorldUpdate();

	// watsonBullet은 normal과 awaken의 애니메이션 차이가 없음
	scale = clips[clipIdx]->GetFrameSize() * size /
		clips[clipIdx]->GetFrameOriginSize();
	clips[clipIdx]->Update();

	OnCollision();
}

void WatsonBullet::Render()
{
	if (!is_active)return;

	VS->Set();
	PS->Set();

	WB->SetVS(0);
	CB->SetPS(0);

	clips[clipIdx]->Render();
	collider->Render();

}

void WatsonBullet::PostRender()
{
	if (!is_active)return;
}

void WatsonBullet::respwan()
{
	nowTime = 0.0f;
	nowHitCount = 0;

	WorldUpdate();
	collider->pos = pos;
	collider->WorldUpdate();

	scale = clips[clipIdx]->GetFrameSize() * collider->Size() /
		clips[clipIdx]->GetFrameOriginSize();

	is_active = true;
	collider->SetActive(true);
	
	hitEnemies.clear();
}

void WatsonBullet::Hit()
{
	nowHitCount++;

	/*if (nowHitCount == maxHitCount)
	{
		is_active = false;
		collider->SetActive(false);
		nowHitCount = 0;
		return;
	}*/
}

void WatsonBullet::OnCollision()
{
	// 충돌 처리
	pair<int, int> pPos = make_pair((int)(pos.x) / CELL_X, (int)(pos.y) / CELL_Y);
	list<Enemy*> enemyList = EnemySpawner::Get()->GetPartition(pPos);
	for (auto e : enemyList)
	{
		if (!e->is_active)continue;

		if ((e->pos - pos).GetLength() < (GetCollider()->Size().GetLength() + e->GetDamageCollider()->Size().GetLength()) / 2.0f)
		{
			if (GetCollider()->isCollision(e->GetDamageCollider()))
			{
				// 이미 충돌한 적이 있다면 넘어가고
				if (hitEnemies.find(e) != hitEnemies.end())continue;
				// 더 이상 부딪힐 횟수가 없다면 이 탄환의 충돌처리 종료
				hitEnemies.insert(e);
				Hit();

				bool isCrt = SkillManager::Get()->GetPlayer()->isCritical();
				if (isCrt)
					e->ChangeHP(-(GetDamage()) * 1.5f, true);
				else
					e->ChangeHP(-(GetDamage()), false);

				if (GetRemainHitCnt() == 0)
				{
					if (isRicochet) // 도탄 생성
					{
						if (ricochetCnt != 0)
						{
							int rand = Random::Get()->GetRandomInt(0, 4);
							switch (rand)
							{
							case 0:
							{
								Vector2 dir = Vector2(-1, -1) * moveDir;
								float newRot = atan(dir.y / dir.x) + 45;
								rot.z = newRot;
								SetDirection(Vector2(cosf(newRot), sinf(newRot)));
							}
							break;
							case 1:
							{
								Vector2 dir = Vector2(-1, -1) * moveDir;
								float newRot = atan(dir.y / dir.x) + 90;
								rot.z = newRot;
								SetDirection(Vector2(cosf(newRot), sinf(newRot)));
							}
							break;
							case 2:
							{
								Vector2 dir = Vector2(-1, -1) * moveDir;
								float newRot = atan(dir.y / dir.x) - 45;
								rot.z = newRot;
								SetDirection(Vector2(cosf(newRot), sinf(newRot)));
							}
							break;
							case 3:
							{
								Vector2 dir = Vector2(-1, -1) * moveDir;
								float newRot = atan(dir.y / dir.x) - 90;
								rot.z = newRot;
								SetDirection(Vector2(cosf(newRot), sinf(newRot)));
							}
							break;
							}
							SetStatus(damage, 250.0f, maxHitCount, 2.0f);
							ricochetCnt--;
							if(ricochetCnt==0)
								isRicochet = false;
							respwan();
							break;
						}
					}
					else
					{
						is_active = false;
						collider->SetActive(false);
					}
				}
			}
		}
	}
}
