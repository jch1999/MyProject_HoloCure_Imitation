#include "framework.h"

Blaze::Blaze(ProjectileSize projSize)
	:Projectile(projSize, 20.0f, 200.0f, 1, 2.0f)
{
	wstring file = L"Textures/Player/PC Computer - HoloCure - Save the Fans - Takanashi Kiara_rm_bg.png";
	Texture* t = Texture::Add(file);

	vector<Frame*> frames;
	Vector2 initPos(7.0f, 3736.0f);
	Vector2 frameSize(38.0f,38.0f);
	for (int i = 0; i < 4; i++)
	{
		frames.push_back(new Frame(file, initPos.x + i * 39.0f, initPos.y
			, frameSize.x, frameSize.y));
	}
	clips.push_back(new Clip(frames, Clip::CLIP_TYPE::PINGPONG, 1 / 4.0f));
	clip_idx = 0;

	colliders.push_back(new RectCollider(size));
	collider = colliders[0];

	is_active = false;
	collider->SetActive(false);
}

Blaze::~Blaze()
{
}

void Blaze::Update()
{
	if (!is_active)return;
	
	nowTime += DELTA;


	WorldUpdate();

	collider->pos = pos;
	collider->rot.z = this->rot.z;
	collider->WorldUpdate();

	scale = clips[clip_idx]->GetFrameSize() * size /
		clips[clip_idx]->GetFrameOriginSize() * 1.5f;

	clips[clip_idx]->Update();
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

	clips[clip_idx]->Render();
	collider->Render();
}

void Blaze::PostRender()
{
	if (!is_active)return;
	// ImGui::Text("Blaze pos : ", (float*)&pos, -WIN_WIDTH, WIN_WIDTH);
	ImGui::Text("Blaze damage : %f", damage);
}

void Blaze::respwan()
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
	clips[clip_idx]->Play();

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
