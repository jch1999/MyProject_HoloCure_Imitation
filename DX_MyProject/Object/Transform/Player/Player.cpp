#include "framework.h"
#include "Player.h"


Player::Player(float inMaxHP, float inAtk, float inSpeed, float inCrtRate, float inPickupRange, float inDamageDelay,int inPickUpRangeIdx,Vector2 inSize)
	:defaultMaxHp(inMaxHP),MaxHP(inMaxHP),HP(inMaxHP)
	,defaultAtk(inAtk),attack(inAtk),defaultSpd(inSpeed),speed(inSpeed)
	,defaultCrt(inCrtRate),crt(inCrtRate),defaultPickUpRange(inPickupRange)
	,damageDelay(inDamageDelay),nowDamageDelay(inDamageDelay)
	,pickUpRangeIdx(inPickUpRangeIdx)
	,nowExp(0.0f),level(1)
	,size(inSize)
	,projCnt(0)
	,colIdxMelee(0),colIdxRange(0),colIdxShot(0)
	,hp_bar(nullptr)
	,hp_back(nullptr)
{
	VS = VertexShader::GetInstance(L"Shader/VertexShader/VertexUV.hlsl", 1);
	PS = PixelShader::GetInstance(L"Shader/PixelShader/PixelUV.hlsl");
	CB = new ColourBuffer();

	SetMaxExp();
}

Player::~Player()
{
	delete CB;

	clips.clear();

	if (damageCollider != nullptr)
		delete damageCollider;

	for (auto p : pickUpColliders)
		delete p;

}

void Player::UpdateDefault()
{
	// ���� �� �ٶ󺸴� ������ ZŰ�� ������ �����ȴ�
	if (!(KEY_CON->Press('Z')))
	{
		atk_arrow->SetID(UI::UI_ID::ATK_ARROW);
	}
	else
	{
		atk_arrow->SetID(UI::UI_ID::ATK_ARROW_FIXED);
	}
}

void Player::CheckMoveDir()
{
	// atk dir arrow �ʱ�ȭ
	if (atk_arrow == nullptr)
	{
		atk_arrow = (Arrow*)(UIManager::Get()->GetUI(UI::UI_ID::ATK_ARROW));
		atk_arrow->SetTarget(this);
		atk_arrow->SetScale(Vector2(2, 2));
		atk_arrow->SetActive(true);
	}

	// �̵� ���� ����
	// �밢�̵�
	if (KEY_CON->Press(VK_LEFT) && KEY_CON->Press(VK_UP))
	{
		moveDir = Vector2(-1.0f, -1.0f).Normalized();
	}
	else if (KEY_CON->Press(VK_LEFT) && KEY_CON->Press(VK_DOWN))
	{
		moveDir = Vector2(-1.0f, 1.0f).Normalized();
	}
	else if (KEY_CON->Press(VK_RIGHT) && KEY_CON->Press(VK_UP))
	{
		moveDir = Vector2(1.0f, -1.0f).Normalized();
	}
	else if (KEY_CON->Press(VK_RIGHT) && KEY_CON->Press(VK_DOWN))
	{
		moveDir = Vector2(1.0f, 1.0f).Normalized();
	}
	// 4���̵�
	else if (KEY_CON->Press(VK_UP))
	{
		moveDir = Vector2(0.0f, -1.0f);
	}
	else if (KEY_CON->Press(VK_DOWN))
	{
		moveDir = Vector2(0.0f, 1.0f);
	}
	else if (KEY_CON->Press(VK_LEFT))
	{
		moveDir = Vector2(-1.0f, 0.0f);
	}
	else if (KEY_CON->Press(VK_RIGHT))
	{
		moveDir = Vector2(1.0f, 0.0f);
	}
	else
	{
		moveDir = Vector2(0.0f, 0.0f);
		return;
	}
	// ���� �� �ٶ󺸴� ������ ZŰ�� ������ �����ȴ�
	if (!(KEY_CON->Press('Z')))
	{
		attackDir = moveDir;
		isLookingRight = attackDir.x > 0.f ? true : attackDir.x < 0.f ? false : isLookingRight;
		atk_arrow->rot.z = attackDir.Angle();
	}
}

void Player::ChangeHP(float amount, Vector2 dir, Enemy* causer)
{
	if (amount > 0 && SkillManager::Get()->isHealDoubled)
	{
		IncreaseHp(amount * 2.0f);
	}
	else
	{
		IncreaseHp(amount);
	}

	// DmgText���
	if (amount < 0)
	{
		int idx = 0;
		DmgText* ui = nullptr;
		Vector2 initPos(pos.x + ((isLookingRight) ? (-damageCollider->Size().x / 4.0f) : (damageCollider->Size().x / 4.0f))
			, pos.y - damageCollider->Size().y / 2.0f);
		int damage = (int)abs(amount);

		while (damage / 10 > 0)
		{
			ui = (DmgText*)(UIManager::Get()->GetUI(UI::UI_ID::PLAYER_DMG_TEXT));
			ui->SetPos(initPos - Vector2(12.0f, 0.0f) * idx++);
			ui->SetMoveDir(dir);
			ui->SetScale(Vector2(1.0f, 1.0f));
			ui->SetClipIdx(damage % 10);
			damage /= 10;
			ui->SetActive(true);
		}
		
		ui = (DmgText*)(UIManager::Get()->GetUI(UI::UI_ID::PLAYER_DMG_TEXT));
		ui->SetPos(initPos - Vector2(12, 0) * idx++);
		ui->SetMoveDir(dir);
		ui->SetScale(Vector2(1.0f, 1.0f));
		ui->SetClipIdx(damage % 10);
		ui->SetActive(true);
	}

	if (HP < MaxHP)
	{
		if (hp_back == nullptr)
		{
			hp_back= (HPBar*)(UIManager::Get()->GetUI(UI::UI_ID::HP_BAR_BACK));
			hp_back->SetTarget(this);
			hp_back->SetScale(Vector2(1, 1));
			hp_back->SetOffset(Vector2(0.0f, -34.5f));
		}
		
		if (hp_bar == nullptr)
		{
			hp_bar = (HPBar*)(UIManager::Get()->GetUI(UI::UI_ID::HP_BAR));
			hp_bar->SetTarget(this);
			hp_bar->SetScale(Vector2(1, 1));
			hp_bar->SetOffset(Vector2(0.0f, -35.0f));
		}

		hp_back->SetHpRate(HP / MaxHP);
		hp_bar->SetHpRate(HP / MaxHP);
	}
	if (HP <= 0.0f)
	{
		is_active = false;
		HP = 0.0f;
	}
	else if (HP >= MaxHP)
	{
		HP = MaxHP;
		if (hp_back != nullptr)
			hp_back->SetHpRate(1.0f);
		if (hp_bar != nullptr)
			hp_bar->SetHpRate(1.0f);
	}
}

void Player::GetExp(float expValue)
{
	nowExp += expValue * (1 + SkillManager::Get()->addExpRate);
	if (exp_bar == nullptr)
	{
		exp_bar = (ExpBar*)(UIManager::Get()->GetUI(UI::UI_ID::EXP_BAR));
		exp_bar->SetActive(true);
	}

	while(nowExp >= nowMaxExp)
	{
		nowExp -= nowMaxExp;
		++level;
		SetMaxExp();
		// ���� �� �� �̺�Ʈ ������ ���� �߰�
		
		UIManager::Get()->IncreaseLevelUpCnt();
	}
	exp_bar->SetExpRate(nowExp / nowMaxExp);
}

void Player::SetMaxExp()
{
	nowMaxExp = (float)(round(pow((4 * (level + 1)), 2.1f)) - round(pow((4 * level), 2.1f)));
}

bool Player::isCritical()
{
	int value = Random::Get()->GetRandomFloat(0.0f, 100.0f);
	if (value < crt)
		return true;
	else
		return false;
}

void Player::SetMaxHP(float inMaxHp)
{
	this->MaxHP = inMaxHp;
}

void Player::IncreaseHp(float inChangeAmount)
{
	HP + inChangeAmount > MaxHP ? HP = MaxHP : HP += inChangeAmount;
}

void Player::DecreaseHp(float inChangeAmount)
{
	HP - inChangeAmount < 0.0f ? HP = 0.0f : HP -= inChangeAmount;
}

void Player::SetATK(float inAtk)
{
	this->attack = inAtk;
}

void Player::SetSPD(float inSpd)
{
	this->speed = inSpd;
}

void Player::SetPickUpRange(int inIdx)
{
	pickUpRangeIdx = inIdx;
}

void Player::IncreasePickUpRange()
{
	if (pickUpColliders.size() - 1 == pickUpRangeIdx)return;

	pickUpColliders[pickUpRangeIdx++]->SetActive(false);
	pickUpColliders[pickUpRangeIdx]->SetActive(true);
}

void Player::SetProjCnt(int cnt)
{
	projCnt = cnt;
}

void Player::SetColIdxMelee(int idx)
{
	colIdxMelee = idx;
}

void Player::SetColIdxShot(int idx)
{
	colIdxShot = idx;
}

void Player::SetColIdxRange(int idx)
{
	colIdxRange = idx;
}
