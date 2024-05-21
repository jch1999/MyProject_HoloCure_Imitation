#include "framework.h"

PhoenixSword::PhoenixSword()
	:Weapon(Skill::SKILL_ID::PHOENIX_SWORD)
{
	minDamage_table = { 0,11.0f, 14.0f,14.0f, 14.0f, 14.0f, 17.0f,5.0f };
	maxDamage_table = { 0,15.0f, 18.0f,18.0f, 18.0f, 18.0f, 21.0f,9.0f };
	colliderIdx_table = { 0,0,0,1,1,1,1,3 };
	hitCooldown_table = { 0,0.33f,0.33f,0.33f,0.33f,0.08f,0.08f,0.07f };
	hiLimit_table = { 0,1,1,1,1,2,2,2 };
	skillDelay_table = { 0, 1.17f, 1.17f, 1.17f, 1.0f, 1.0f, 1.0f, 1.0f };
	blaze_hitCool = 1.0f;

	slash = new KiaraSlash();
	for (int i = 0; i < 10; i++)
	{
		blazes.push_back(new Blaze());
	}

	now_skill_delay = 0.0f;
	playTime_table.push_back(1.0f);
	play_time = 0.0f;
	enhanceDamage = 0.0f;
}

PhoenixSword::~PhoenixSword()
{
	delete slash;
	for (auto b : blazes)
		delete b;
}

void PhoenixSword::Update()
{
	if (now_level == 0)return;
	switch (action_status)
	{
	case Skill::SKILL_STATUS::COOLDOWN:
	{
		now_skill_delay += DELTA;

		if (now_skill_delay >= skillDelay_table[now_level])
		{
			now_skill_delay = 0.0f;
			action_status = Skill::SKILL_STATUS::PLAY;

			// slash ���� �ʱ�ȭ
			float damage = Random::Get()->GetRandomInt(minDamage_table[now_level], maxDamage_table[now_level] + 1)
				+ player->GetATK((UINT)Weapon::WEAPON_TYPE::MELEE)
				+ enhanceDamage;
			slash->SetStatus(damage, 250.0f, -1, playTime_table[0]);
			slash->SetDirection(player->GetAttackDir());
			slash->rot.z = atan(player->GetAttackDir().y / player->GetAttackDir().x);
			slash->SetColliderIdx(colliderIdx_table[now_level] + player->GetColIdxMelee());
			slash->SetClipIdx(((now_level == max_level) ? 1 : 0));
			slash->respwan();
		}
	}
		break;
	case Skill::SKILL_STATUS::PLAY:
	{
		play_time += DELTA;

		if (slash->GetCollider()->is_active&&play_time>=0.5f)
		{
			slash->GetCollider()->SetActive(false); 
		}

		if (play_time > playTime_table[0])
		{
			play_time = 0.0f;
			enemyCooltimes_s.clear();
			enemyHitCount.clear();
			enemyNowFrame_s.clear();
			removeList_s.clear();
			action_status = Skill::SKILL_STATUS::COOLDOWN;
			slash->is_active = false;
			return;
		}
		else
		{
			UpdateSlash();
		}
	}
		break;
	default:
		break;
	}

	UpdateBlaze();
}

void PhoenixSword::Render()
{
	if (now_level == 0)return;

	slash->Render();
	for (auto b : blazes)
		b->Render();
}

void PhoenixSword::PostRender()
{
	if (now_level == 0)return;

	ImGui::Text("PhoenixBlade's skill level : %d", now_level);
	switch (action_status)
	{
	case Skill::SKILL_STATUS::COOLDOWN:
		ImGui::Text("now status : cooldown");
		break;
	case Skill::SKILL_STATUS::PLAY:
		ImGui::Text("now status : play");
		break;
	default:
		break;
	}
	slash->PostRender();
	
	for (auto b : blazes)
		b->PostRender();
}

bool PhoenixSword::LevelUp()
{
	if (now_level != max_level)
	{
		now_level++;
		return true;
	}
	else
	{
		enhanceDamage += 2.0f;
	}
	return false;
}

void PhoenixSword::UpdateSlash()
{
	slash->pos = player->pos + slash->move_dir * 60.0f;
	slash->Update();

	// �浹 ���� Enemey ����
	enemyNowFrame_s.clear();
	removeList_s.clear();
	//const vector<Enemy*>& enemyList = EnemySpawner::Get()->GetEnemyList();
	// Slash�� pos�� CELL ��ġ�� �߾����� 3x3 ������ �˻�
	/*pair<int, int> sPos = make_pair(slash->pos.x / CELL_X, slash->pos.y / CELL_Y);
	for (int i = -1; i <= 1; i++)
	{
		for (int j = -1; j <= 1; j++)
		{
			list<Enemy*> enemyList = EnemySpawner::Get()->GetPartition(make_pair(sPos.first + i, sPos.second + j));
			for (auto e : enemyList)
			{
				if (!e->is_active)continue;
				if (slash->GetCollider()->isCollision(e->GetDamageCollider()))
					enemyNowFrame_s.push_back(e);
			}
		}
	}*/
	
	
	/*
	// ���� �浹 Enemey�� �̹� ������ �浹 Enemy ��
	// �̹� �����ӿ� �������� ������ ���� ����Ʈ�� �ֱ�
	for (auto m : enemyCooltimes_s)
	{
		bool isExist = false;
		for (auto e : enemyNowFrame_s)
		{
			if (m.first == e)
			{
				isExist = true;
				break;
			}
		}
		if (!isExist)
		{
			removeList_s.push_back(m.first);
		}
	}

	// ����
	for (auto e : removeList_s)
	{
		enemyCooltimes_s.erase(enemyCooltimes_s.find(e));
	}
	*/
	// ����Ʈ ����
	for (auto e : enemyNowFrame_s)
	{
		auto found = enemyCooltimes_s.find(e);
		// ������ �������� ���� - �߰� �� �ٷ� �����ϰ� ����
		if (found == enemyCooltimes_s.end())
		{
			enemyCooltimes_s[e] = 0.0f;
			enemyHitCount[e] = 0;
		}
		// ������ ���� - �ð� ����
		else
		{
			enemyCooltimes_s[e] = found->second - DELTA;
		}
	}

	// �ð� ��� üũ, coolTime�� �������� damage�ֱ�
	for (auto m : enemyCooltimes_s)
	{
		//m.second -= DELTA;
		if (m.second <= 0.0f)
		{
			if (enemyHitCount[m.first] < hiLimit_table[now_level])
			{
				m.second = hitCooldown_table[now_level];
				m.first->GetDamage(slash->GetDamage());
				enemyHitCount[m.first]++;
			}
			// �̹� ���� Enemy�� ���� ����Ʈ�� �߰�
			if (!m.first->is_active)
			{
				removeList_s.push_back(m.first);
			}

			// ���� ���� + 25% Ȯ���̸�
			// enemy�� ����ٴϸ� ���ӵ������� �ִ� �� ����
			if (now_level == max_level)
			{
				int rand = Random::Get()->GetRandomInt(0, 4);
				if (rand == 0)
				{
					// enemy ��ġ�� blaze ����
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
						+ player->GetATK((UINT)Weapon::WEAPON_TYPE::MELEE)
						+ enhanceDamage;
					blaze->SetStatus(damage * 0.2f, 0.0f, -1, 5.0f);
					blaze->respwan();
				}
			}
		}
	}

	// ����
	for (auto e : removeList_s)
	{
		enemyCooltimes_s.erase(enemyCooltimes_s.find(e));
	}
}

void PhoenixSword::UpdateBlaze()
{
	for (auto b : blazes)
	{
		if (!b->is_active)continue;
		b->Update();
		if (!b->is_active) // �ð��� ���� ��Ȱ��ȭ
		{
			enemyCooltimes_b.clear();
			enemyNowFrame_b.clear();
			removeList_b.clear();
			continue;
		}
		enemyNowFrame_b.clear();
		removeList_b.clear();

		const vector<Enemy*>& enemyList = EnemySpawner::Get()->GetEnemyList();
		for (auto e : enemyList)
		{
			if (!e->is_active)continue;
			if (b->GetCollider()->isCollision(e->GetDamageCollider()))
				enemyNowFrame_s.push_back(e);
		}

		/*
		// ���� �浹 Enemey�� �̹� ������ �浹 Enemy ��
		// �̹� �����ӿ� �������� ������ ���� ����Ʈ�� �ֱ�
		for (auto m : enemyCooltimes_b)
		{
			bool isExist = false;
			for (auto e : enemyNowFrame_b)
			{
				if (m.first == e)
				{
					if(e->is_active)
						isExist = true;
					break;
				}
			}
			if (!isExist)
			{
				removeList_b.push_back(m.first);
			}
		}

		// ����
		for (auto e : removeList_b)
		{
			enemyCooltimes_b.erase(enemyCooltimes_b.find(e));
		}
		*/

		// ������ �������� ������ �߰�, �����ϸ� �ð� ���
		for (auto e : enemyNowFrame_s)
		{
			auto found = enemyCooltimes_b.find(e);
			if (found == enemyCooltimes_b.end())
			{
				enemyCooltimes_b[e] = 0.0f;
			}
			else
			{
				enemyCooltimes_b[found->first] = found->second - DELTA;
			}
		}

		// �ð� ��� üũ, coolTime�� �������� damage�ֱ�
		for (auto m : enemyCooltimes_b)
		{
			
			//m.second -= DELTA;
			if (m.second <= 0.0f)
			{
				m.second = blaze_hitCool;
				m.first->GetDamage(b->GetDamage());
				
				if (!m.first->is_active)
				{
					removeList_b.push_back(m.first);
				}
			}
		}

		// ����
		for (auto e : removeList_b)
		{
			enemyCooltimes_b.erase(enemyCooltimes_b.find(e));
		}
	}
}

bool PhoenixSword::LevelDown()
{
	if (now_level > 0)
	{
		now_level--;
		return true;
	}
	return false;
}