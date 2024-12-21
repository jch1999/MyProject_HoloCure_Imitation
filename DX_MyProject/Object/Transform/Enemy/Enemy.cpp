#include "framework.h"

Enemy::Enemy(float inMaxHP, float inAttack, float inSpdRate, float inAtkDelay,int inDropExp)
	:MaxHP(inMaxHP),HP(inMaxHP),attack(inAttack), spdRate(inSpdRate)
	,atkDelay(inAtkDelay),atkNowTime(inAtkDelay),dropExp(inDropExp)
{
	VS = VertexShader::GetInstance(L"Shader/VertexShader/VertexUV.hlsl", 1);
	PS = PixelShader::GetInstance(L"Shader/PixelShader/PixelUV.hlsl");
	CB = new ColourBuffer();

	for (UINT i = 0; i < (UINT)Enemy::BAD_STATUS::END; i++)
		badStatusTable.push_back(0.0f);
}

Enemy::~Enemy()
{
	delete CB;

	clips.clear();

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
		Vector2 initPos(pos.x + ((isLookingRight) ? (-damageCollider->Size().x / 4.0f) : (damageCollider->Size().x / 4.0f))
			, pos.y - damageCollider->Size().y / 4.0f);
		int damage = (int)abs(amount);

		while (damage / 10 > 0)
		{
			if (isCrt)
				ui = (DmgText*)(UIManager::Get()->GetUI(UI::UI_ID::CRT_DMG_TEXT));
			else
				ui = (DmgText*)(UIManager::Get()->GetUI(UI::UI_ID::DMG_TEXT));
			ui->SetPos(initPos - Vector2(12.f, 0.0f) * idx++);
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
		ui->SetPos(initPos - Vector2(12, 0) * idx++);
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
				ItemSpawner::Get()->GenerateItem(pos + Vector2(cosf(rot), sinf(rot)) * 30.0f, Item::ITEM_ID::EXP, dropExp / 10.0f);
			}
			ItemSpawner::Get()->GenerateItem(pos, Item::ITEM_ID::REWORD_BOX, ItemSpawner::Get()->coinValue);

			// Box 생성 기능 추후 추가
		}
		break;
		default:
			ItemSpawner::Get()->GenerateItem(pos, dropExp);
			break;
		}

	}
	else if (HP > MaxHP)
		HP = MaxHP;
}

void Enemy::Attack()
{
	if (!is_active)return;

	atkNowTime = 0.0f;
	Vector2 dir = Vector2(-moveDir.x, abs(moveDir.y));
	player->ChangeHP(-attack, dir, this);
}

void Enemy::SetColor(Float4 inColor)
{
	CB->data.colour = inColor;
}

void Enemy::SetMoveDir(Vector2 inDir)
{
	moveDir = inDir;
}

void Enemy::SetBadStatus(Enemy::BAD_STATUS bad, float time)
{
	if (badStatusTable[(UINT)bad] < time)
		badStatusTable[(UINT)bad] = time;
}

void Enemy::Move()
{
	float moveSPD = defaultSPD * spdRate;
	if (badStatusTable[(UINT)Enemy::BAD_STATUS::UPSIDE_DOWN] > 0.0f)
		moveSPD *= 0.0f;
	else if (badStatusTable[(UINT)Enemy::BAD_STATUS::FROZEN] > 0.0f)
		moveSPD *= 0.7f;

	for (list<KnockBackData>::iterator iter = knockbackList.begin(); iter != knockbackList.end(); iter++)
	{
		if (iter->remainTime > 0.f)
		{
			iter->remainTime -= DELTA;
			pos += iter->knockBackDir * iter->spd * DELTA;
		}
	}

	switch (type)
	{
	case Enemy::MOVE_TYPE::CHASE:
	{
		if (dirSetDelay >= 0.33f)
		{
			Vector2 dir = player->pos - pos;
			dir.Normalize();
			moveDir = dir;
			dirSetDelay = 0.0f;
		}
		else
		{
			dirSetDelay += DELTA;
		}

		if (addtionalDir.GetLength() > 0.1f)
			moveDir = (moveDir + addtionalDir).Normalized();
		pos += moveDir * moveSPD * DELTA;
	}
		break;
	case Enemy::MOVE_TYPE::WAVE:
	{

	}
		break;
	case Enemy::MOVE_TYPE::STRAIGHT:
	{
		Vector2 dir = destination - pos;
		moveDir = dir.Normalized();

		if (addtionalDir.GetLength() > 0.1f)
			moveDir = (moveDir + addtionalDir).Normalized();
		pos += moveDir * moveSPD * DELTA;
	}
		break;
	default:
		break;
	}
	isLookingRight = (player->pos - pos).x > 0.0f;
}

void Enemy::SetDest(Vector2 inDestination)
{
	destination = inDestination;
}

void Enemy::SetPlayer(Player* target)
{
	player = target;
}

void Enemy::SetStatus(float MaxHP, float atk, float spdRate, float atk_delay,int drop_exp)
{
	this->MaxHP = MaxHP;
	this->attack = atk;
	this->spdRate = spdRate;
	this->atkDelay = atk_delay;
	this->dropExp = drop_exp;
}

void Enemy::Respawn()
{
	HP = MaxHP;
	atkNowTime = atkDelay;
	knockbackList.clear();

	is_active = true;
	damageCollider->SetActive(true);
	attackCollider->SetActive(true);
	dirSetDelay = 0.33f;

	WorldUpdate();
	damageCollider->pos = pos;
	damageCollider->WorldUpdate();
	attackCollider->pos = pos;
	attackCollider->WorldUpdate();
}

void Enemy::SetAdditionalDirection(Vector2 inDir)
{
	addtionalDir = inDir;
}

void Enemy::SetKnockBack(Vector2 dir, float spd, float time)
{
	//pair<int, int> key = make_pair(round(dir.x), round(dir.y));
	//knockback_map[key] += time;
	KnockBackData data;
	data.knockBackDir = dir;
	data.spd = spd;
	data.remainTime = time;
	knockbackList.push_back(data);
}
