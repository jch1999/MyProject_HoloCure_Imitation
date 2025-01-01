#include "framework.h"

vector<shared_ptr<const Frame>>& Blaze::GetBlazeFrames()
{
	static vector<shared_ptr<const Frame>> blazeFrames;
	return blazeFrames;
}

int& Blaze::GetBlazeUseCnt()
{
	static int blazeUseCnt = 0;
	return blazeUseCnt;
}

Blaze::Blaze(ProjectileSize projSize)
	:Projectile(projSize, 20.0f, 200.0f, 1, 2.0f)
{
	if (GetBlazeFrames().empty())
	{
		InitFrame();
	}

	clips.push_back(make_shared<Clip>(GetBlazeFrames(), Clip::CLIP_TYPE::PINGPONG, 1 / 4.0f));
	clipIdx = 0;

	colliders.push_back(new RectCollider(size));
	collider = colliders[0];

	is_active = false;
	collider->SetActive(false);

	++GetBlazeUseCnt();
}

Blaze::~Blaze()
{
	if ((--GetBlazeUseCnt()) == 0)
	{
		ClearFrame();
	}
}

void Blaze::Update()
{
	if (!is_active)return;
	
	nowTime += DELTA;


	WorldUpdate();

	collider->pos = pos;
	collider->rot.z = this->rot.z;
	collider->WorldUpdate();

	scale = clips[clipIdx]->GetFrameSize() * size /
		clips[clipIdx]->GetFrameOriginSize() * 1.5f;

	clips[clipIdx]->Update();
	if (nowTime >= lifeTime)
		is_active = false;
	else
		OnCollision();
}

void Blaze::Render()
{
	if (!is_active)return;

	VS->Set();
	PS->Set();

	WB->SetVS(0);
	CB->SetPS(0);

	clips[clipIdx]->Render();
	collider->Render();
}

void Blaze::respwan()
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
	clips[clipIdx]->Play();

	hitEnemies.clear();
	cooltimeList.clear();
	enemyNowFrame.clear();
	removeCooltimeList.clear();
}

void Blaze::Hit()
{
	nowHitCount++;

	if (nowHitCount == maxHitCount)
	{
		is_active = false;
		nowHitCount = 0;
		return;
	}
}

void Blaze::OnCollision()
{
	enemyNowFrame.clear();
	removeCooltimeList.clear();

	const vector<Enemy*>& enemyList = EnemySpawner::Get()->GetEnemyList();
	for (auto e : enemyList)
	{
		if (!e->is_active)continue;
		if (GetCollider()->isCollision(e->GetDamageCollider()))
			enemyNowFrame.push_back(e);
	}

	// 기존에 존재하지 않으면 추가, 존재하면 시간 경과
	for (auto e : enemyNowFrame)
	{
		auto found = hitEnemies.find(e);
		if (found == hitEnemies.end())
		{
			hitEnemies.insert(e);
			cooltimeList.push_back(make_pair(e, 0.0f));
		}
	}

	// 시간 경과 체크, coolTime이 지났으면 damage주기
	list<pair<Enemy*, float>>::iterator iter = cooltimeList.begin();
	for (; iter != cooltimeList.end(); iter++)
	{
		iter->second -= DELTA;
		if (iter->second <= 0.0f)
		{
			iter->second = hitCoolDown;
			// blaze.. 크리티컬 적용 o x? 일단 x로
			iter->first->ChangeHP(-(GetDamage()), false);

			if (!iter->first->is_active)
			{
				removeCooltimeList.push_back(*iter);
			}
		}
	}

	// 제거
	for (auto r : removeCooltimeList)
	{
		hitEnemies.erase(r.first);
		cooltimeList.remove(r);
	}
}

void Blaze::InitFrame()
{
	auto& blazeFrames = GetBlazeFrames();
	if (!blazeFrames.empty()) return;

	wstring file = L"Textures/Player/PC Computer - HoloCure - Save the Fans - Takanashi Kiara_rm_bg.png";

	Vector2 initPos(7.0f, 3736.0f);
	Vector2 frameSize(38.0f, 38.0f);
	for (int i = 0; i < 4; i++)
	{
		blazeFrames.push_back(make_shared<const Frame>(file, initPos.x + i * 39.0f, initPos.y
			, frameSize.x, frameSize.y));
	}
}

void Blaze::ClearFrame()
{
	GetBlazeFrames().clear();
}