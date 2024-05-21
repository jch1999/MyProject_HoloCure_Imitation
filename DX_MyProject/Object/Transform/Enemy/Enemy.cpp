#include "framework.h"

Enemy::Enemy(float MaxHP, float attack, float spdRate, float atk_delay,int drop_exp)
	:MaxHP(MaxHP),HP(MaxHP),attack(attack), spdRate(spdRate)
	,atk_delay(atk_delay),atk_nowTime(atk_delay),drop_exp(drop_exp)
{
	VS = VertexShader::GetInstance(L"Shader/VertexShader/VertexUV.hlsl", 1);
	PS = PixelShader::GetInstance(L"Shader/PixelShader/PixelUV.hlsl");
	CB = new ColourBuffer();

	for (UINT i = 0; i < (UINT)Enemy::BAD_STATUS::END; i++)
		badStatus_table.push_back(0.0f);
}

Enemy::~Enemy()
{
	delete CB;

	for (Clip* c : clips)
	{
		if (c != nullptr)
			delete c;
	}

	for (auto c : damageColliders)
		delete c;
	for (auto c : atkColliders)
		delete c;
}

void Enemy::SetBadStatus(Enemy::BAD_STATUS bad, float time)
{
	if (badStatus_table[(UINT)bad] < time)
		badStatus_table[(UINT)bad] = time;
}

void Enemy::Move()
{
	float moveSPD = defaultSPD * spdRate;
	if (badStatus_table[(UINT)Enemy::BAD_STATUS::UPSIDE_DOWN] > 0.0f)
		moveSPD *= 0.0f;
	else if (badStatus_table[(UINT)Enemy::BAD_STATUS::FROZEN] > 0.0f)
		moveSPD *= 0.7f;

	for (int i=0;i<knockbackTime_list.size();i++)
	{
		if (knockbackTime_list[i]>0.0f)
		{
			knockbackTime_list[i] -= DELTA;
			addtional_dir += Vector2(knockbackDir_list[i].first, knockbackDir_list[i].second);
		}
	}

	switch (type)
	{
	case Enemy::MOVE_TYPE::CHASE:
	{
		if (dir_set_delay >= 0.33f)
		{
			Vector2 dir = player->pos - pos;
			dir.Normalize();
			move_dir = dir;
			dir_set_delay = 0.0f;
		}
		else
		{
			dir_set_delay += DELTA;
		}

		pos += move_dir * moveSPD * DELTA;
	}
		break;
	case Enemy::MOVE_TYPE::WAVE:
	{

	}
		break;
	case Enemy::MOVE_TYPE::STRAIGHT:
	{
		Vector2 dir = dest - pos;
		move_dir = dir.Normalized();
		pos += move_dir * moveSPD * DELTA;
	}
		break;
	default:
		break;
	}
	
	pos += addtional_dir.Normalized() * moveSPD * DELTA;

	is_looking_right = move_dir.x > 0.0f;
}

void Enemy::SetStatus(float MaxHP, float atk, float spdRate, float atk_delay,int drop_exp)
{
	this->MaxHP = MaxHP;
	this->attack = atk;
	this->spdRate = spdRate;
	this->atk_delay = atk_delay;
	this->drop_exp = drop_exp;
}

void Enemy::Respawn()
{
	HP = MaxHP;
	atk_nowTime = atk_delay;

	is_active = true;
	damageCollider->SetActive(true);
	attackCollider->SetActive(true);
	dir_set_delay = 0.33f;

	WorldUpdate();
	damageCollider->pos = pos;
	damageCollider->WorldUpdate();
	attackCollider->pos = pos;
	attackCollider->WorldUpdate();
}

void Enemy::SetKnockBack(Vector2 dir, float time)
{
	pair<int, int> newDir = make_pair(dir.x, dir.y);
	for (int i = 0; i < knockbackDir_list.size(); i++)
	{
		if (newDir == knockbackDir_list[i])
		{
			knockbackTime_list[i] += time;
			return;
		}
	}

	knockbackDir_list.push_back(newDir);
	knockbackTime_list.push_back(time);
}
