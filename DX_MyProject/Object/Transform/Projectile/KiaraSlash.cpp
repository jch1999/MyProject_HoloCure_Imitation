#include "framework.h"

KiaraSlash::KiaraSlash(Vector2 size)
	:Projectile(20.0f, 200.0f, 1, 2.0f)
{
	wstring file = L"Textures/Player/PC Computer - HoloCure - Save the Fans - Takanashi Kiara_rm_bg.png";
	Texture* t = Texture::Add(file);

	this->size = size;
	vector<Frame*> frames;

	// PROJ_STATE::NORMAL
	Vector2 initPos(7.0f, 711.0f);
	Vector2 frame_size(185.0f, 133.0f);
	for (int i = 0; i < 5; i++)
	{
		frames.push_back(new Frame(file, initPos.x + 186.0f * i, initPos.y
			, frame_size.x, frame_size.y));
	}
	clips.push_back(new Clip(frames, Clip::CLIP_TYPE::END, 1.0f / 7.5f));
	frames.clear();

	// PROJ_STATE::AWAKEN
	initPos = Vector2(7.0f, 861.0f);
	frame_size = Vector2(182.0f, 136.0f);
	for (int i = 0; i < 8; i++)
	{
		frames.push_back(new Frame(file, initPos.x + 186.0f * i, initPos.y
			, frame_size.x, frame_size.y));
	}
	clips.push_back(new Clip(frames, Clip::CLIP_TYPE::END, 1.0f / 12.0f));
	frames.clear();

	// 0~2 : PhoenixSword스킬의 기본 collider 설정,
	colliders.push_back(new RectCollider(size));
	colliders.push_back(new RectCollider(size * 1.25f));

	idx_collider;
	collider = colliders[idx_collider];
	collider->pos = pos + move_dir * 50.0f;
}

KiaraSlash::~KiaraSlash()
{
}

void KiaraSlash::Update()
{
	if (!is_active)return;

	// player - kiara와 일정거리에서 이동하지 않음
	// pos += move_dir * speed * DELTA;
	nowTime += DELTA;

	if (nowTime >= lifeTime)
	{
		is_active = false;
		nowTime = 0.0f;
	}

	WorldUpdate();

	collider->pos = pos + move_dir * 20.0f;
	collider->rot.z = this->rot.z;
	collider->WorldUpdate();

	scale = clips[clip_idx]->GetFrameSize() * collider->Size() /
		clips[clip_idx]->GetFrameOriginSize() * Vector2(1.2f,1.0f);

	if (move_dir.x < 0.0f)
		scale = scale * Vector2(-1.0f, 1.0f);

	clips[clip_idx]->Update();
}

void KiaraSlash::Render()
{
	if (!is_active)return;

	VS->Set();
	PS->Set();

	WB->SetVS(0);
	CB->SetPS(0);

	clips[clip_idx]->Render();
	collider->Render();

}

void KiaraSlash::PostRender()
{
	if (!is_active)return;
	ImGui::Text("Now damage : %f", damage);
}

void KiaraSlash::respwan()
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
}
void KiaraSlash::Hit()
{
	// maxHitCount=-1일때는 hit 제한이 없다는 것
	if (maxHitCount == -1)return;

	nowHitCount++;

	if (nowHitCount == maxHitCount)
	{
		is_active = false;
		nowHitCount = 0;
		return;
	}
}

void KiaraSlash::OnCollision()
{
	// 충돌 중인 Enemey 검출
	enemyNowFrame.clear();
	removeList.clear();
	//const vector<Enemy*>& enemyList = EnemySpawner::Get()->GetEnemyList();
	// Slash의 pos의 CELL 위치를 중앙으로 3x3 영역을 검사
	pair<int, int> sPos = make_pair(pos.x / CELL_X, pos.y / CELL_Y);
	list<Enemy*> enemyList = EnemySpawner::Get()->GetPartition(make_pair(sPos.first, sPos.second));
	for (auto e : enemyList)
	{
		if (!e->is_active)continue;
		if (GetCollider()->isCollision(e->GetDamageCollider()))
			enemyNowFrame.push_back(e);
	}

	// 리스트 갱신
	for (auto e : enemyNowFrame)
	{
		// 기존에 존재하지 않음 - 추가 및 바로 공격하게 설정
		if (hitEnemies.find(e) == hitEnemies.end())
		{
			cooltimeList.push_back(make_pair(e, 0.0f));
			hitEnemies.insert(e);
		}
	}

	// 시간 경과 체크, coolTime이 지났으면 damage주기
	list<pair<Enemy*, float>>::iterator iter = cooltimeList.begin();
	for (; iter != cooltimeList.end(); iter++)
	{
		iter->second -= DELTA;
		if (iter->second <= 0.0f)
		{
			if (enemyHitCount[m.first] < hitLimit_table[now_level])
			{
				enemyCooltimes_s[m.first] = hitCooldown_table[now_level];
				if (player->isCritical())
				{
					m.first->ChangeHP(-(slash->GetDamage()) * 1.5f, true);
				}
				else
				{
					m.first->ChangeHP(-(slash->GetDamage()), false);
				}
				enemyHitCount[m.first]++;

				// 각성 상태 + 25% 확률이면
				// enemy를 따라다니며 지속데미지를 주는 불 생성
				if (now_level == max_level)
				{
					int rand = Random::Get()->GetRandomInt(0, 4);
					if (rand == 0)
					{
						// enemy 위치에 blaze 생성
						Projectile* blaze = nullptr;
						for (auto b : blazes)
						{
							if (!b->is_active)
							{
								blaze = b;
								break;
							}
						}
						if (blaze == nullptr)
						{
							blaze = new Blaze();
							blazes.push_back(blaze);
						}
						blaze->pos = m.first->pos;
						float damage = Random::Get()->GetRandomInt(minDamage_table[now_level], maxDamage_table[now_level] + 1)
							+ player->GetATK()
							+ enhanceDamage;
						blaze->SetStatus(damage * 0.2f, 0.0f, -1, 5.0f);
						blaze->respwan();
					}
				}
			}
			// 이미 죽은 Enemy를 제거 리스트에 추가
			if (!m.first->is_active)
			{
				removeList_s.push_back(m.first);
			}


		}
	}

	// 제거
	for (auto e : removeList_s)
	{
		enemyCooltimes_s.erase(enemyCooltimes_s.find(e));
	}
}
