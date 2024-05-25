#include "framework.h"
#include "Player.h"


Player::Player(float MaxHP, float atk, float speed, float crt, float pickupRange, float damage_delay,int idx_pickUpRange,Vector2 size)
	:default_maxHp(MaxHP),MaxHP(MaxHP),HP(MaxHP)
	,default_atk(atk),attack(atk),default_spd(speed),speed(speed)
	,default_crt(crt),crt(crt),default_pickUpRange(pickupRange)
	,damage_delay(damage_delay),now_damage_delay(damage_delay)
	,idx_pickUpRange(idx_pickUpRange)
	,nowExp(0.0f),level(1)
	,size(size)
	,projCnt(0)
	,colIdx_Melee(0),colIdx_Range(0),colIdx_Shot(0)
	,damage_Melee(0.0f),damage_Range(0.0f),damage_Shot(0.0f)
{
	VS = VertexShader::GetInstance(L"Shader/VertexShader/VertexUV.hlsl", 1);
	PS = PixelShader::GetInstance(L"Shader/PixelShader/PixelUV.hlsl");
	CB = new ColourBuffer();


	expLimits.push_back(0);
	expLimits.push_back(100);
	for (int i = 1; i < 100; i++)
	{
		expLimits.push_back(expLimits[i] * 1.45f);
	}
}

Player::~Player()
{
	delete VS;
	delete PS;
	delete CB;

	for (Clip* c : clips)
	{
		if (c != nullptr)
			delete c;
	}
	if (damageCollider != nullptr)
		delete damageCollider;

	for (auto p : pickUpColliders)
		delete p;

}

void Player::CheckMoveDir()
{
	// 이동 방향 지정
	// 대각이동
	if (KEY_CON->Press(VK_LEFT) && KEY_CON->Press(VK_UP))
	{
		move_dir = Vector2(-1.0f, -1.0f).Normalized();
	}
	else if (KEY_CON->Press(VK_LEFT) && KEY_CON->Press(VK_DOWN))
	{
		move_dir = Vector2(-1.0f, 1.0f).Normalized();
	}
	else if (KEY_CON->Press(VK_RIGHT) && KEY_CON->Press(VK_UP))
	{
		move_dir = Vector2(1.0f, -1.0f).Normalized();
	}
	else if (KEY_CON->Press(VK_RIGHT) && KEY_CON->Press(VK_DOWN))
	{
		move_dir = Vector2(1.0f, 1.0f).Normalized();
	}
	// 4방이동
	else if (KEY_CON->Press(VK_UP))
	{
		move_dir = Vector2(0.0f, -1.0f);
	}
	else if (KEY_CON->Press(VK_DOWN))
	{
		move_dir = Vector2(0.0f, 1.0f);
	}
	else if (KEY_CON->Press(VK_LEFT))
	{
		move_dir = Vector2(-1.0f, 0.0f);
	}
	else if (KEY_CON->Press(VK_RIGHT))
	{
		move_dir = Vector2(1.0f, 0.0f);
	}
	else
	{
		move_dir = Vector2(0.0f, 0.0f);
		return;
	}
	// 공격 및 바라보는 방향은 Z키를 누르면 고정된다
	if (!(KEY_CON->Press('Z')))
	{
		attack_dir = move_dir;
		is_looking_right = attack_dir.x > 0.f ? true : attack_dir.x < 0.f ? false : is_looking_right;
	}
}

void Player::ChangeHP(float amount)
{
	HP += amount;
	if (HP < MaxHP)
	{
		UIManager::Get()->GetUI(UI::UI_ID::HP_BAR)->SetSize(Vector2(HP / MaxHP, 1.0f));
	}
	if (HP <= 0.0f)
		is_active = false;
	else if (HP > MaxHP)
		HP = MaxHP;
}

void Player::GetExp(int expValue)
{
	nowExp += expValue;
	if (nowExp >= expLimits[level])
	{
		nowExp -= expLimits[level];
		level++;
		// 레벨 업 시 이벤트 내용은 추후 추가
		switch (player_id)
		{
		case Player::PLAYER_ID::WATSON:
		{
			if(SkillManager::Get()->GetSkillByID(Skill::SKILL_ID::PISTOL_SHOT)->GetLevelUpAble())
				SkillManager::Get()->GetSkillByID(Skill::SKILL_ID::PISTOL_SHOT)->LevelUp();
		}
			break;
		case Player::PLAYER_ID::KIARA:
		{
			if (SkillManager::Get()->GetSkillByID(Skill::SKILL_ID::PHOENIX_SWORD)->GetLevelUpAble())
				SkillManager::Get()->GetSkillByID(Skill::SKILL_ID::PHOENIX_SWORD)->LevelUp();
		}
			break;
		case Player::PLAYER_ID::BAELZ:
		{
			if (SkillManager::Get()->GetSkillByID(Skill::SKILL_ID::PLAY_DICE)->GetLevelUpAble())
				SkillManager::Get()->GetSkillByID(Skill::SKILL_ID::PLAY_DICE)->LevelUp();
		}
			break;
		default:
			break;
		}
	}
}

bool Player::isCritical()
{
	int value = Random::Get()->GetRandomInt(0, 100);
	if (value < crt)
		return true;
	else
		return false;
}

float Player::GetATK(UINT type)
{
	switch (type)
	{
	case (UINT)Weapon::WEAPON_TYPE::MULTI_SHOT:
		return attack + damage_Shot;
	case (UINT)Weapon::WEAPON_TYPE::RANGE:
		return attack + damage_Range;
	case (UINT)Weapon::WEAPON_TYPE::MELEE:
		return attack + damage_Melee;
	default:
		return attack;
	}
}
