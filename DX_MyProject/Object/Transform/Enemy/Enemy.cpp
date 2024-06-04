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

void Enemy::ChangeHP(float amount,bool isCrt)
{
	HP += amount;

	// DmgText출력
	if (amount < 0)
	{
		int idx = 0;
		DmgText* ui = nullptr;
		Vector2 initPos(pos.x + ((is_looking_right) ? (-damageCollider->Size().x / 4.0f) : (damageCollider->Size().x / 4.0f))
			, pos.y - damageCollider->Size().y / 4.0f);
		int damage = (int)abs(amount);

		while (damage / 10 > 0)
		{
			if (isCrt)
				ui = (DmgText*)(UIManager::Get()->GetUI(UI::UI_ID::CRT_DMG_TEXT));
			else
				ui = (DmgText*)(UIManager::Get()->GetUI(UI::UI_ID::DMG_TEXT));
			ui->SetPos(initPos - Vector2(6, 0) * idx++);
			ui->SetMoveDir(initPos.Normalized()*Vector2(1.0f,-1.0f));
			ui->SetScale(Vector2(1.0f, 1.0f));
			ui->SetClipIdx(damage % 10);
			damage /= 10;
			ui->SetActive(true);
		}
		if (isCrt)
			ui = (DmgText*)(UIManager::Get()->GetUI(UI::UI_ID::CRT_DMG_TEXT));
		else
			ui = (DmgText*)(UIManager::Get()->GetUI(UI::UI_ID::DMG_TEXT));
		ui->SetPos(initPos - Vector2(6, 0) * idx++);
		ui->SetMoveDir(initPos.Normalized() * Vector2(1.0f, -1.0f));
		ui->SetScale(Vector2(1.0f, 1.0f));
		ui->SetClipIdx(damage % 10);
		ui->SetActive(true);
	}

	if (HP <= 0.0f)
	{
		is_active = false;
		EnemySpawner::Get()->EnemyDead();
		switch (id)
		{
		case ENEMY_ID::MINI_BOSS:
		{
			for (int i = 0; i < 10; i++)
			{
				float rot = i * 36.0f;
				ItemSpawner::Get()->GenerateItem(pos + Vector2(cosf(rot), sinf(rot)) * 30.0f, Item::ITEM_ID::EXP, drop_exp / 10.0f);
			}
			ItemSpawner::Get()->GenerateItem(pos, Item::ITEM_ID::REWORD_BOX, ItemSpawner::Get()->coinValue);

			// Box 생성 기능 추후 추가
		}
		break;
		default:
			ItemSpawner::Get()->GenerateItem(pos, drop_exp);
			break;
		}

	}
	else if (HP > MaxHP)
		HP = MaxHP;
}

void Enemy::Attack()
{
	if (!is_active)return;

	atk_nowTime = 0.0f;
	Vector2 dir = Vector2(-move_dir.x, abs(move_dir.y));
	player->ChangeHP(-attack, dir);
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

	for (auto knockback:knockback_map)
	{
		if (knockback.second>0.f)
		{
			knockback_map[knockback.first] -= DELTA;
			addtional_dir += Vector2(knockback.first.first, knockback.first.second);
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

		if (addtional_dir.GetLength() > 0.1f)
			move_dir = (move_dir + addtional_dir).Normalized();
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

		if (addtional_dir.GetLength() > 0.1f)
			move_dir = (move_dir + addtional_dir).Normalized();
		pos += move_dir * moveSPD * DELTA;
	}
		break;
	default:
		break;
	}
	is_looking_right = (player->pos - pos).x > 0.0f;
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
	pair<int, int> key = make_pair(round(dir.x), round(dir.y));
	knockback_map[key] += time;
}
