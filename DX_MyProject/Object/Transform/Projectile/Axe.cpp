#include "framework.h"

Axe::Axe(Vector2 size)
	:Projectile()
{
	wstring file = L"Textures/Skill/PC Computer - HoloCure - Save the Fans - Weapons_rm_bg.png";
	Texture* t = Texture::Add(file);

	this->size = size;
	vector<Frame*> frames;
	Vector2 initPos(4.0f, 1616.0f);
	Vector2 frameSize(46.0f, 46.0f);
	/*for (int i = 0; i < 8; i++)
	{
		frames.push_back(new Frame(file, initPos.x + i * 48.0f, initPos.y
			, frameSize.x, frameSize.y));
	}
	clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP, 1 / 8.0f));*/
	frames.push_back(new Frame(file, initPos.x, initPos.y, frameSize.x, frameSize.y));
	clips.push_back(new Clip(frames, Clip::CLIP_TYPE::END, 1.0f));
	clip_idx = 0;

	colliders.push_back(new CircleCollider(size.x * 0.5f));
	colliders.push_back(new CircleCollider(size.x * 0.6f));
	colliders.push_back(new CircleCollider(size.x * 0.72f));
	colliders.push_back(new CircleCollider(size.x * 1.08f));
	collider = colliders[0];

	is_active = false;
	collider->SetActive(false);
}

Axe::~Axe()
{
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
		pos += Up() * speed * DELTA + move_dir * speed * 0.5f * DELTA;
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

	clips[clip_idx]->Render();
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
	removeList.clear();

	for (auto e : enemyList)
	{
		if (e->is_active)
		{
			// 面倒 贸府
			float minDist = GetCollider()->Size().GetLength() + e->GetDamageCollider()->Size().GetLength();
			float differDist = (e->pos - pos).GetLength();
			if (minDist > differDist)
			{
				if (GetCollider()->isCollision(e->GetDamageCollider()))
				{
					enemyNowFrame.push_back(e);
					if (hitEnemies.find(e) == hitEnemies.end())
					{
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
		(*iter).second -= DELTA;
		if ((*iter).second <= 0.0f)
		{
			// 单固瘤 林扁
			if (find(enemyNowFrame.begin(), enemyNowFrame.end(), (*iter).first) == enemyNowFrame.end())
			{
				removeCooltimeList.push_back((*iter));
			}
			else
			{
				(*iter).first->ChangeHP(-(GetDamage()), isCrt);

				(*iter).second = hitCoolDown;
			}
		}
	}

	for (int i = 0; i < removeCooltimeList.size(); i++)
	{
		cooltimeList.remove(removeCooltimeList[i]);
	}
}

void Axe::respwan()
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
