#include "framework.h"


vector<vector<shared_ptr<const Frame>>>& BaelzDice::GetDiceFrames()
{
	static vector<vector<shared_ptr<const Frame>>> diceFrames;
	return diceFrames;
}

int& BaelzDice::GetDiceiceUseCnt()
{
	static int diceUseCnt = 0;
	return diceUseCnt;
}

BaelzDice::BaelzDice(ProjectileSize projSize)
	:Projectile(projSize)
	, isRicochet(false),ricochetCnt(0)
	,isAwaken(false)
{
	if (GetDiceFrames().empty())
	{
		InitFrame();
	}

	for (int i = 0; i < 2; i++)
	{
		RectCollider* collider = new RectCollider(size * (1.0f + i * 0.3f));
		colliders.push_back(collider);
	}

	colliderIdx = 0;
	collider = colliders[colliderIdx];
	collider->pos = pos;
	clipIdx = 0;

	auto& currentFrame = GetDiceFrames()[isAwaken ? 1 : 0][clipIdx];
	scale = currentFrame->GetFrameSize() * collider->Size() /
		currentFrame->GetFrameOriginSize();

	is_active = false;
	collider->SetActive(false);

	++GetDiceiceUseCnt();
}

BaelzDice::~BaelzDice()
{
	if ((--GetDiceiceUseCnt()) == 0)
	{
		ClearFrame();
	}
}

void BaelzDice::Update()
{
	if (!is_active)return;
	
	pos += moveDir * speed * DELTA;
	
	moveDist += (moveDir * speed * DELTA).GetLength();
	if (moveDist >= targetDist) // 다 이동하면 멈춘다
	{
		collider->SetActive(false);
		moveDir = Vector2(0.0f, 0.0f);
	}
	else
	{
		OnCollision();
	}

	nowTime += DELTA;
	if (nowTime >= lifeTime)
	{
		is_active = false;
		moveDist = 0.0f;
		nowTime = 0.0f;
		hitEnemies.clear();
		return;
	}

	WorldUpdate();

	collider->pos = pos;
	collider->rot.z = this->rot.z;
	collider->WorldUpdate();

	auto& currentFrame = GetDiceFrames()[isAwaken ? 1 : 0][clipIdx];
	scale = currentFrame->GetFrameSize() * collider->Size() /
		currentFrame->GetFrameOriginSize();
}

void BaelzDice::Render()
{
	if (!is_active)return;

	VS->Set();
	PS->Set();

	WB->SetVS(0);
	CB->SetPS(0);

	GetDiceFrames()[isAwaken ? 1 : 0][clipIdx]->Render();
	collider->Render();
}

void BaelzDice::respwan()
{
	moveDist = 0.0f;
	nowHitCount = 0;
	
	WorldUpdate();
	collider->pos = pos;
	collider->WorldUpdate();

	auto& currentFrame = GetDiceFrames()[isAwaken ? 1 : 0][clipIdx];
	scale = currentFrame->GetFrameSize() * collider->Size() /
		currentFrame->GetFrameOriginSize();

	is_active = true;
	collider->SetActive(true);
}

void BaelzDice::Hit()
{
	// maxHitCount=-1일때는 hit 제한이 없다는 것
	if (maxHitCount == -1)return;

	nowHitCount++;

	if (nowHitCount == maxHitCount)
	{
		collider->SetActive(false);
		nowHitCount = 0;
		moveDir = Vector2(0.0f, 0.0f);
		moveDist = 0.0f;
		hitEnemies.clear();
		return;
	}
}

void BaelzDice::OnCollision()
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
				if (hitEnemies.find(e) != hitEnemies.end())
					continue;

				bool isCrt = SkillManager::Get()->GetPlayer()->isCritical();
				if (isCrt)
					e->ChangeHP(-(GetDamage()) * 1.5f, true);
				else
					e->ChangeHP(-(GetDamage()), false);

				Hit();
				
				if (isKnockback)
					e->SetKnockBack(moveDir, 200.0f, 0.2f);
				hitEnemies.insert(e);

				if (isRicochet) // 도탄 생성
				{
					if (ricochetCnt>0)
					{
						float newRot = Random::Get()->GetRandomFloat(0, 360.0f);
						SetDirection(Vector2(cosf(newRot), sinf(newRot)));
						rot.z = newRot;
						ricochetCnt--;
						respwan();
						break;
					}
					else
					{
						isRicochet = false;
					}
				}
			}
		}
	}
}

void BaelzDice::SetRicochetInfo(bool inIsRicochet, int inCnt)
{
	this->isRicochet = inIsRicochet;
	ricochetCnt = inCnt;
}

void BaelzDice::ActiveAwaken()
{
	isAwaken = true;
}

void BaelzDice::DeactiveAwken()
{
	isAwaken = false;
}

void BaelzDice::InitFrame()
{
	auto& frames = GetDiceFrames();
	if (!(frames.empty())) return;

	wstring file = L"Textures/Player/PC Computer - HoloCure - Save the Fans - Hakos Baelz_rm_bg.png";

	// Normal Dice
	Vector2 initPos(32.0f, 582.0f);
	Vector2 frame_size(18.0f, 18.0f);
	{
		vector<shared_ptr<const Frame>> normalDiceFrmaes;
		for (int i = 0; i < 6; i++)
		{
			normalDiceFrmaes.emplace_back(make_shared<const Frame>(file, initPos.x + 65.0f * i, initPos.y
				, frame_size.x, frame_size.y));
		}
		frames.push_back(normalDiceFrmaes);
	}
	// Awaken Dice
	initPos = Vector2(32.0f, 663.0f);
	{
		vector<shared_ptr<const Frame>> awakenDiceFrmaes;
		for (int i = 0; i < 6; i++)
		{
			awakenDiceFrmaes.emplace_back(make_shared<const Frame>(file, initPos.x + 65.0f * i, initPos.y
				, frame_size.x, frame_size.y));
		}
		frames.push_back(awakenDiceFrmaes);
	}
}

void BaelzDice::ClearFrame()
{
	GetDiceFrames().clear();
}
