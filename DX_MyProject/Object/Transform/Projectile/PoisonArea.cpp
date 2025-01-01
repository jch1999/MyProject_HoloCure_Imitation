#include "framework.h"


shared_ptr<const Frame>& PoisonArea::GetPoisonFrame()
{
	static shared_ptr<const Frame> poisonFrame;
	return poisonFrame;
}

int& PoisonArea::GetPoisonUseCnt()
{
	static int poisonUseCnt = 0;
	return poisonUseCnt;
}

PoisonArea::PoisonArea(ProjectileSize projSize)
	:Projectile(projSize, 20.0f, 200.0f, 1, 2.0f)
{
	if (!GetPoisonFrame())
	{
		InitFrame();
	}
	// 0~2 : SpiderCooking스킬의 기본 collider 설정,
	colliders.push_back(new CircleCollider(size.x * 0.5f));
	colliders.push_back(new CircleCollider(size.x * 0.5f * 1.15f)); // SpiderCooking LV 2
	colliders.push_back(new CircleCollider(size.x * 0.5f * 1.25f)); // SpiderCooking LV 4

	colliderIdx=0;
	collider = colliders[colliderIdx];
	collider->pos = pos;
	CB->data.colour = Float4(1.0f, 1.0f, 1.0f, 0.5f);
	++GetPoisonUseCnt();
}

PoisonArea::~PoisonArea()
{
	if ((--GetPoisonUseCnt()) == 0)
	{
		ClearFrame();
	}
}
void PoisonArea::Update()
{
	if (!is_active)return;

	WorldUpdate();

	collider->pos = pos;
	collider->WorldUpdate();

	scale = GetPoisonFrame()->GetFrameSize() * collider->Size() /
		GetPoisonFrame()->GetFrameOriginSize();

	OnCollision();
}

void PoisonArea::Render()
{
	if (!is_active)return;

	VS->Set();
	PS->Set();

	WB->SetVS(0);
	CB->SetPS(0);

	GetPoisonFrame()->Render();
	collider->Render();
}

void PoisonArea::respwan()
{
	// 한 번 활성화되면 재활성될 일은 없음
	return;
}

void PoisonArea::OnCollision()
{
	// 충돌 중인 Enemey 검출
	enemyNowFrame.clear();
	removeCooltimeList.clear();
	//const vector<Enemy*>& enemyList = EnemySpawner::Get()->GetEnemyList();
	// Slash의 pos의 CELL 위치를 중앙으로 3x3 영역을 검사
	// EnemySpawner에서 가운데 cell을 기준으로 3x3 크기에 포함되는 적들 정보를 저장했는데 여기서
	// 또 3x3으로 검사하면 9번 들어가려나?
	pair<int, int> sPos = make_pair(pos.x / CELL_X, pos.y / CELL_Y);
	list<Enemy*> enemyList = EnemySpawner::Get()->GetPartition(make_pair(sPos.first, sPos.second));
	for (auto e : enemyList)
	{
		if (!e->is_active)continue;
		// 콜라이더 중점 사이의 거리 < 콜라이더 길이의 합 일 때만 충돌 검사
		float sumLength = GetCollider()->Size().GetLength() + e->GetDamageCollider()->Size().GetLength();
		float dist = (GetCollider()->pos - e->GetDamageCollider()->pos).GetLength();
		if (sumLength >= dist)
		{
			if (GetCollider()->isCollision(e->GetDamageCollider()))
				enemyNowFrame.push_back(e);
		}
	}

	// 새롭게 추가한 에너미 추가
	for (auto e : enemyNowFrame)
	{
		// 기존에 존재하지 않음 - 추가 및 바로 공격하게 설정
		if (hitEnemies.find(e) == hitEnemies.end())
		{
			hitEnemies.insert(e);
			cooltimeList.push_back(make_pair(e, 0.0f));
		}
	}

	// 시간 경과 체크, coolTime이 지났으면 damage주기
	list<pair<Enemy*, float>>::iterator iter = cooltimeList.begin();
	for(; iter != cooltimeList.end();iter++)
	{
		iter->second -= DELTA;
		if (iter->second <= 0.0f)
		{
			// 현재 충돌 중이라면
			if (find(enemyNowFrame.begin(), enemyNowFrame.end(), iter->first) != enemyNowFrame.end())
			{
				iter->second = hitCoolDown;

				damage = dynamic_cast<SpiderCooking*>(SkillManager::Get()->GetSkillByID(Skill::SKILL_ID::SPIDER_COOKING))->GetDamage();
				if (SkillManager::Get()->GetPlayer()->isCritical())
				{
					iter->first->ChangeHP(-damage * 1.5f, true);
				}
				else
				{
					iter->first->ChangeHP(-damage, false);
				}
				if (isKnockback)
					iter->first->SetKnockBack(iter->first->GetMoveDir() * -1.0f, 300.0f, 0.13f);

				// 이미 죽은 Enemy를 제거 리스트에 추가
				if (!(iter->first->is_active))
				{
					removeCooltimeList.push_back((*iter));
				}
			}
			else // 충돌하지 않은 상태로 충돌 대기시간이 지났다면 제거
			{
				removeCooltimeList.push_back((*iter));
			}
		}
	}

	// 제거
	for (auto e : removeCooltimeList)
	{
		cooltimeList.remove(e);
		hitEnemies.erase(e.first);
	}
}

void PoisonArea::Hit()
{
	// 충돌 횟수 제한 없음
	return;
}

void PoisonArea::InitFrame()
{
	if (GetPoisonFrame()) return;
	wstring file = L"Textures/Skill/PC Computer - HoloCure - Save the Fans - Weapons_rm_bg.png";

	// PROJ_STATE::NORMAL
	GetPoisonFrame() = make_shared<const Frame>(file, 4.0f, 80.0f, 107.0f, 107.0f);
}

void PoisonArea::ClearFrame()
{
	GetPoisonFrame().reset();
}
