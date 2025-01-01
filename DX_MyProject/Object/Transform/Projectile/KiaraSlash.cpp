#include "framework.h"




vector<vector<shared_ptr<const Frame>>>& KiaraSlash::GetSlashFrames()
{
	static vector<vector<shared_ptr<const Frame>>> slashFrames;
	return slashFrames;
}

int& KiaraSlash::SlashUseCnt()
{
	static int slashUseCnt = 0;
	return slashUseCnt;
}

KiaraSlash::KiaraSlash(ProjectileSize projSize)
	:Projectile(projSize,20.0f, 200.0f, 1, 2.0f)
	, isAwaken(false)
{
	if (GetSlashFrames().empty())
	{
		InitFrame();
	}

	auto& slashFrames = GetSlashFrames();
	for (auto& frames:slashFrames)
	{
		clips.push_back(make_shared<Clip>(frames, Clip::CLIP_TYPE::END, 1.0f / 7.5f));
	}

	// 0~2 : PhoenixSword��ų�� �⺻ collider ����,
	colliders.push_back(new RectCollider(size));
	colliders.push_back(new RectCollider(size * 1.25f));

	colliderIdx = 0;
	collider = colliders[colliderIdx];
	collider->pos = pos + moveDir * 50.0f;

	hitLimitCnt = 0;

	++SlashUseCnt();
}

KiaraSlash::~KiaraSlash()
{
	if ((--SlashUseCnt()) == 0)
	{
		ClearFrame();
	}
}

void KiaraSlash::Update()
{
	if (!is_active)return;

	// player - kiara�� �����Ÿ����� �̵����� ����
	// pos += move_dir * speed * DELTA;
	nowTime += DELTA;

	if (nowTime >= lifeTime)
	{
		is_active = false;
		nowTime = 0.0f;
	}

	WorldUpdate();

	collider->pos = pos + moveDir * 20.0f;
	collider->rot.z = this->rot.z;
	collider->WorldUpdate();

	scale = clips[clipIdx]->GetFrameSize() * collider->Size() /
		clips[clipIdx]->GetFrameOriginSize() * Vector2(1.2f,1.0f);

	if (moveDir.x < 0.0f)
		scale = scale * Vector2(-1.0f, 1.0f);

	clips[clipIdx]->Update();

	OnCollision();
}

void KiaraSlash::Render()
{
	if (!is_active)return;

	VS->Set();
	PS->Set();

	WB->SetVS(0);
	CB->SetPS(0);

	clips[clipIdx]->Render();
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
	scale = clips[clipIdx]->GetFrameSize() * collider->Size() /
		clips[clipIdx]->GetFrameOriginSize();
	
	is_active = true;
	collider->SetActive(true);
	clips[clipIdx]->Play();

	hitEnemies.clear();
	enemyNowFrame.clear();
	cooltimeList.clear();
	enemyHitCount.clear();
	removeCooltimeList.clear();
}
void KiaraSlash::Hit()
{
	// maxHitCount=-1�϶��� hit ������ ���ٴ� ��
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
	// �浹 ���� Enemey ����
	enemyNowFrame.clear();
	removeList.clear();
	//const vector<Enemy*>& enemyList = EnemySpawner::Get()->GetEnemyList();
	// Slash�� pos�� CELL ��ġ�� �߾����� 3x3 ������ �˻�
	pair<int, int> sPos = make_pair(pos.x / CELL_X, pos.y / CELL_Y);
	list<Enemy*> enemyList = EnemySpawner::Get()->GetPartition(make_pair(sPos.first, sPos.second));
	for (auto e : enemyList)
	{
		if (!e->is_active)continue;
		if (GetCollider()->isCollision(e->GetDamageCollider()))
			enemyNowFrame.push_back(e);
	}

	// ����Ʈ ����
	for (auto e : enemyNowFrame)
	{
		// ������ �������� ���� - �߰� �� �ٷ� �����ϰ� ����
		if (hitEnemies.find(e) == hitEnemies.end())
		{
			cooltimeList.push_back(make_pair(e, 0.0f));
			hitEnemies.insert(e);
		}
	}

	// �ð� ��� üũ, coolTime�� �������� damage�ֱ�
	list<pair<Enemy*, float>>::iterator iter = cooltimeList.begin();
	for (; iter != cooltimeList.end(); iter++)
	{
		iter->second -= DELTA;
		if (iter->second <= 0.0f)
		{
			if (enemyHitCount[iter->first] < hitLimitCnt)
			{
				iter->second = hitCoolDown;
				if (Owner->GetPlayer()->isCritical())
				{
					iter->first->ChangeHP(-(GetDamage()) * 1.5f, true);
				}
				else
				{
					iter->first->ChangeHP(-(GetDamage()), false);
				}
				enemyHitCount[iter->first]++;

				// ���� ���� + 25% Ȯ���̸�
				// enemy�� ����ٴϸ� ���ӵ������� �ִ� �� ����
				if (isAwaken)
				{
					int rand = Random::Get()->GetRandomInt(0, 4);
					if (rand == 0)
					{
						// enemy ��ġ�� blaze ����
						Projectile* blaze = dynamic_cast<PhoenixSword*>(Owner)->GetBlaze();
						blaze->pos = iter->first->pos;
						blaze->respwan();
					}
				}
			}
			// �̹� ���� Enemy�� ���� ����Ʈ�� �߰�
			if (!iter->first->is_active)
			{
				removeCooltimeList.push_back(*iter);
			}


		}
	}

	// ����
	for (auto r : removeCooltimeList)
	{
		hitEnemies.erase(r.first);
		cooltimeList.remove(r);
	}
}

void KiaraSlash::ActiveAwaken()
{
	isAwaken = true;
}

void KiaraSlash::DeactiveAwaken()
{
	isAwaken = false;
}

void KiaraSlash::InitFrame()
{
	auto& slashFrmaes = GetSlashFrames();
	if (!slashFrmaes.empty()) return;

	wstring file = L"Textures/Player/PC Computer - HoloCure - Save the Fans - Takanashi Kiara_rm_bg.png";

	// PROJ_STATE::NORMAL
	Vector2 initPos(7.0f, 711.0f);
	Vector2 frame_size(185.0f, 133.0f);
	{
		vector<shared_ptr<const Frame>> normalSlashFrmaes;
		for (int i = 0; i < 5; i++)
		{
			normalSlashFrmaes.push_back(make_shared<const Frame>(file, initPos.x + 186.0f * i, initPos.y
				, frame_size.x, frame_size.y));
		}
		slashFrmaes.emplace_back(normalSlashFrmaes);
	}

	// PROJ_STATE::AWAKEN
	initPos = Vector2(7.0f, 861.0f);
	frame_size = Vector2(182.0f, 136.0f);
	{
		vector<shared_ptr<const Frame>> awakenSlashFrmaes;
		for (int i = 0; i < 8; i++)
		{
			awakenSlashFrmaes.push_back(make_shared<const Frame>(file, initPos.x + 186.0f * i, initPos.y
				, frame_size.x, frame_size.y));
		}
		slashFrmaes.emplace_back(awakenSlashFrmaes);
	}
}

void KiaraSlash::ClearFrame()
{
	GetSlashFrames().clear();
}