#include "framework.h"

BaelzDice::BaelzDice(ProjectileSize projSize)
	:Projectile(projSize)
	, isRicochet(false),ricochetCnt(0)
{
	wstring file = L"Textures/Player/PC Computer - HoloCure - Save the Fans - Hakos Baelz_rm_bg.png";
	Texture* t = Texture::Add(file);

	vector<Frame*> frames;
	// Normal Dice
	Vector2 initPos(32.0f, 582.0f);
	Vector2 frame_size(18.0f, 18.0f);
	for (int i = 0; i < 6; i++)
	{
		frames.push_back(new Frame(file, initPos.x + 65.0f * i, initPos.y
			, frame_size.x, frame_size.y));
		clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP, 1.0f / 1.0f));
		frames.clear();
	}
	// Awaken Dice
	initPos = Vector2(32.0f, 663.0f);

	for (int i = 0; i < 6; i++)
	{
		frames.push_back(new Frame(file, initPos.x + 65.0f * i, initPos.y
			, frame_size.x, frame_size.y));
		clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP, 1.0f / 1.0f));
		frames.clear();
	}

	for (int i = 0; i < 2; i++)
	{
		RectCollider* collider = new RectCollider(size * (1.0f + i * 0.3f));
		colliders.push_back(collider);
	}

	idx_collider = 0;
	collider = colliders[idx_collider];
	collider->pos = pos;
	clip_idx = 0;
	scale = clips[clip_idx]->GetFrameSize() * collider->Size() /
		clips[clip_idx]->GetFrameOriginSize();

	is_active = false;
	collider->SetActive(false);

}

BaelzDice::~BaelzDice()
{
}

void BaelzDice::Update()
{
	if (!is_active)return;
	
	pos += move_dir * speed * DELTA;
	
	moveDist += (move_dir * speed * DELTA).GetLength();
	if (moveDist >= targetDist) // 다 이동하면 멈춘다
	{
		collider->SetActive(false);
		move_dir = Vector2(0.0f, 0.0f);
		// 다 이동하고 나면 시간 체크를 시작
		nowTime += DELTA;
	}
	else
	{
		OnCollision();
	}

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

	scale = clips[clip_idx]->GetFrameSize() * collider->Size() /
		clips[clip_idx]->GetFrameOriginSize();

	clips[clip_idx]->Update();
}

void BaelzDice::Render()
{
	if (!is_active)return;

	VS->Set();
	PS->Set();

	WB->SetVS(0);
	CB->SetPS(0);

	clips[clip_idx]->Render();
	collider->Render();
}

void BaelzDice::PostRender()
{
}

void BaelzDice::respwan()
{
	moveDist = 0.0f;
	nowHitCount = 0;
	
	WorldUpdate();
	collider->pos = pos;
	collider->WorldUpdate();
	scale = clips[clip_idx]->GetFrameSize() * collider->Size() /
		clips[clip_idx]->GetFrameOriginSize();

	is_active = true;
	collider->SetActive(true);
	clips[clip_idx]->Play();
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
		move_dir = Vector2(0.0f, 0.0f);
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
					e->SetKnockBack(move_dir, 200.0f, 0.2f);
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
