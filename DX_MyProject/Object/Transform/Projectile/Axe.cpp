#include "framework.h"

shared_ptr<const Frame>& Axe::GetAxeFrame()
{
	static shared_ptr<const Frame> axeFrame;
	return axeFrame;
}

int& Axe::GetAxeUseCnt()
{
	static int axeUseCnt = 0;
	return axeUseCnt;
}

Axe::Axe(ProjectileSize projSize)
	:Projectile(projSize)
{
	if (GetAxeFrame() == nullptr)
	{
		InitFrame();
	}

	colliders.push_back(new CircleCollider(size.x * 0.5f));
	colliders.push_back(new CircleCollider(size.x * 0.6f));
	colliders.push_back(new CircleCollider(size.x * 0.72f));
	colliders.push_back(new CircleCollider(size.x * 1.08f));
	collider = colliders[0];

	is_active = false;
	collider->SetActive(false);

	++GetAxeUseCnt();
}

Axe::~Axe()
{
	if ((--GetAxeUseCnt()) == 0)
	{
		ClearFrame();
	}
}

void Axe::InitFrame()
{
	auto& axeFrame = GetAxeFrame();
	if (axeFrame) return;

	wstring file = L"Textures/Skill/PC Computer - HoloCure - Save the Fans - Weapons_rm_bg.png";
	
	Vector2 initPos(4.0f, 1616.0f);
	Vector2 frameSize(46.0f, 46.0f);
	
	axeFrame=make_shared<const Frame>(file, initPos.x, initPos.y, frameSize.x, frameSize.y);
}

void Axe::ClearFrame()
{
	GetAxeFrame().reset();
}

void Axe::Update()
{
	if (!is_active)return;;

	if (nowTime >= lifeTime)
	{
		SetActive(false);
		collider->SetActive(false);
	}
	else
	{
		rot.z += rotSpeed * DELTA;
		pos += Up() * speed * DELTA + moveDir * speed * 0.5f * DELTA;
		WorldUpdate();

		collider->rot.z = rot.z;
		collider->pos = pos;
		collider->WorldUpdate();

		nowTime += DELTA;
		rotSpeed -= rotSpeed * 0.3f * DELTA;
	}
	OnCollision();
}

void Axe::Render()
{
	if (!is_active)return;

	VS->Set();
	PS->Set();

	WB->SetVS(0);
	CB->SetPS(0);

	GetAxeFrame()->Render();
	collider->Render();
}

void Axe::PostRender()
{
}

void Axe::OnCollision()
{
	pair<int, int> pPos = make_pair((int)(pos.x) / CELL_X, (int)(pos.y) / CELL_Y);
	list<Enemy*> enemyList = EnemySpawner::Get()->GetPartition(pPos);
	enemyNowFrame.clear();
	removeCooltimeList.clear();

	for (auto e : enemyList)
	{
		if (e->is_active)
		{
			// 충돌 처리
			float minDist = GetCollider()->Size().GetLength() + e->GetDamageCollider()->Size().GetLength();
			float differDist = (e->pos - pos).GetLength();
			if (minDist > differDist)
			{
				if (GetCollider()->isCollision(e->GetDamageCollider()))
				{
					enemyNowFrame.push_back(e);
					if (hitEnemies.find(e) == hitEnemies.end())
					{
						hitEnemies.insert(e);
						cooltimeList.push_back(make_pair(e, 0.0f));
						Hit();
					}
				}
			}
		}
	}

	list<pair<Enemy*, float>>::iterator iter = cooltimeList.begin();
	for (; iter != cooltimeList.end(); iter++)
	{
		iter->second -= DELTA;
		if (iter->second <= 0.0f)
		{
			// 데미지 주기
			// 없으면 리스트에서 제거
			if (find(enemyNowFrame.begin(), enemyNowFrame.end(), iter->first) == enemyNowFrame.end())
			{
				removeCooltimeList.push_back((*iter));
			}
			else
			{
				bool isCrt = SkillManager::Get()->GetPlayer()->isCritical();
				if (isCrt)
					iter->first->ChangeHP(-(GetDamage()) * 1.5f, true);
				else
					iter->first->ChangeHP(-(GetDamage()), false);

				iter->second = hitCoolDown;
			}
		}
	}

	for (int i = 0; i < removeCooltimeList.size(); i++)
	{
		cooltimeList.remove(removeCooltimeList[i]);
		hitEnemies.erase(removeCooltimeList[i].first);
	}
}

void Axe::respwan()
{
	nowTime = 0.0f;
	nowHitCount = 0;

	WorldUpdate();
	collider->pos = pos;
	collider->WorldUpdate();

	scale = GetAxeFrame()->GetFrameSize() * collider->Size() /
		GetAxeFrame()->GetFrameOriginSize();

	is_active = true;
	collider->SetActive(true);
	rot.z = 0.0f;

	cooltimeList.clear();
}

void Axe::Hit()
{
	nowHitCount++;

	if (nowHitCount == maxHitCount)
	{
		is_active = false;
		nowHitCount = 0;
		return;
	}

}
