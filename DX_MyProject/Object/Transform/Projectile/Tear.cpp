#include "framework.h"

Tear::Tear(Vector2 size)
	:Projectile()
{
	wstring file = L"Textures/Skill/PC Computer - HoloCure - Save the Fans - Weapons_rm_bg.png";
	Texture* t = Texture::Add(file);

	this->size = size;
	vector<Frame*> frames;
	frames.push_back(new Frame(file, 4.0f, 946.0f, 10.0f, 8.0f));
	clips.push_back(new Clip(frames, Clip::CLIP_TYPE::END, 1 / 1.0f));
	clip_idx = 0;

	colliders.push_back(new RectCollider(size * 1.5f));
	collider = colliders[0];

	is_active = false;
	collider->SetActive(false);
}

Tear::~Tear()
{
}

void Tear::Update()
{
	if (!is_active)return;

	nowTime += DELTA;
	if (nowTime >= lifeTime)
	{
		nowTime = 0.0f;
		is_active = false;
		collider->SetActive(false);
		return;
	}
	pos = pos + move_dir * speed * DELTA;
	WorldUpdate();
	
	collider->pos = pos;
	collider->rot = this->rot;
	collider->WorldUpdate();

	scale = clips[clip_idx]->GetFrameSize() * collider->Size() /
		clips[clip_idx]->GetFrameOriginSize();

	clips[clip_idx]->Update();

	OnCollision();
}

void Tear::Render()
{
	if (!is_active)return;

	VS->Set();
	PS->Set();

	WB->SetVS(0);
	CB->SetPS(0);

	clips[clip_idx]->Render();
	collider->Render();
}

void Tear::PostRender()
{
}

void Tear::respwan()
{
	nowTime = 0.0f;
	nowHitCount = 0;

	WorldUpdate();
	collider->pos = pos;
	collider->WorldUpdate();

	scale = clips[clip_idx]->GetFrameSize() * collider->Size() /
		clips[clip_idx]->GetFrameOriginSize();

	is_active = true;
	collider->SetActive(true);
}

void Tear::Hit()
{
	nowHitCount++;

	if (nowHitCount == maxHitCount)
	{
		is_active = false;
		nowHitCount = 0;
		return;
	}
}

void Tear::OnCollision()
{
	pair<int, int> tPos = make_pair((int)(pos.x) / CELL_X, (int)(pos.y) / CELL_Y);
	list<Enemy*> enemyList = EnemySpawner::Get()->GetPartition(tPos);
	for (auto e : enemyList)
	{
		if (e->is_active)
		{
			float minDist = (GetCollider()->Size().GetLength() + e->GetDamageCollider()->Size().GetLength()) / 2.0f;
			float dist = (pos - e->pos).GetLength();
			if (minDist >= dist)
			{
				if (GetCollider()->isCollision(e->GetDamageCollider()))
				{
					Hit();
					bool isCrt = Owner->GetPlayer()->isCritical();
					e->ChangeHP(-GetDamage(), isCrt);
					break;
				}
			}
		}
	}
}
