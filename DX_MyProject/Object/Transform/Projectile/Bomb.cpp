#include "framework.h"

Bomb::Bomb(ProjectileSize projSize, float targetDist, Vector2 move_dir)
	:Projectile(projSize, 20.0f, 200.0f, 1, 2.0f)
{
	this->targetDist = targetDist;
	this->move_dir = move_dir;
	wstring file = L"Textures/Skill/PC Computer - HoloCure - Save the Fans - Weapons_rm_bg.png";
	Texture* t = Texture::Add(file);

	vector<Frame*> frames;
	frames.push_back(new Frame(file, 416.0f, 1508.0f, 23.0f, 29.0f));
	clips.push_back(new Clip(frames, Clip::CLIP_TYPE::END, 1));
	clip_idx = 0;

	colliders.push_back(new RectCollider(size * Vector2(1.2f, 1.2f)));
	collider = colliders[0];

	explosion = new ExplosionSmoke();
	is_active = false;
	collider->SetActive(false);
	
}

Bomb::~Bomb()
{
}

void Bomb::Update()
{
	if (is_active|| explosion->is_active)
	{
		if (is_active)
		{
			pos = LERP(pos, targetPos, speed * DELTA);
			if ((pos - targetPos).GetLength() < 0.1f)
			{
				pos = targetPos;
			}

			WorldUpdate();

			collider->pos = pos;
			collider->WorldUpdate();

			scale = clips[clip_idx]->GetFrameSize() * collider->Size() /
				clips[clip_idx]->GetFrameOriginSize();

			clips[clip_idx]->Update();


			OnCollision();
		}
		if(explosion->is_active)
			explosion->Update();
	}
		
}

void Bomb::Render()
{
	if (is_active)
	{
		VS->Set();
		PS->Set();

		WB->SetVS(0);
		CB->SetPS(0);

		clips[clip_idx]->Render();
		collider->Render();
	}
	if (explosion->is_active)
	{
		explosion->Render();
	}
}

void Bomb::PostRender()
{
}

void Bomb::respwan()
{
	WorldUpdate();
	collider->pos = pos;
	collider->WorldUpdate();
	scale = clips[clip_idx]->GetFrameSize() * collider->Size() /
		clips[clip_idx]->GetFrameOriginSize();

	moveDist = 0.0f;
	SetActive(true);
	collider->SetActive(true);
}

void Bomb::OnCollision()
{
	pair<int, int> pPos = make_pair((int)(pos.x) / CELL_X, (int)(pos.y) / CELL_Y);
	list<Enemy*> enemyList = EnemySpawner::Get()->GetPartition(pPos);
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
					Hit();

					// explosion 활성화
					// status는 HoloBomb에서 설정 중
					//explosion->SetStatus(GetDamage(), 250.0f, hitCount, -1.0f);
					explosion->pos = pos;
					explosion->SetOwner(GetOwner());
					explosion->respwan();
					break;
				}
			}
		}
	}
}

void Bomb::Hit()
{
	SetActive(false);
	collider->SetActive(false);
}

void Bomb::SetExplosionStatus(float damage, float speed, int hitCount, float lifeTime, float hitCoolDown)
{
	explosion->SetStatus(damage, speed, hitCount, lifeTime, hitCoolDown);
}
