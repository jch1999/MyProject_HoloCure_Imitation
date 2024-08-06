#include "framework.h"
#include "Player.h"


Player::Player(float MaxHP, float atk, float speed, float crt, float pickupRange, float damage_delay,int idx_pickUpRange,Vector2 size)
	:default_maxHp(MaxHP),MaxHP(default_maxHp),HP(default_maxHp)
	,default_atk(atk),attack(default_atk),default_spd(speed),speed(default_spd)
	,default_crt(crt),crt(default_crt),default_pickUpRange(pickupRange)
	,damage_delay(damage_delay),now_damage_delay(damage_delay)
	,idx_pickUpRange(idx_pickUpRange)
	,nowExp(0.0f),level(1)
	,size(size)
	,projCnt(0)
	,colIdx_Melee(0),colIdx_Range(0),colIdx_Shot(0)
	,hp_bar(nullptr)
	,hp_back(nullptr)
{
	VS = VertexShader::GetInstance(L"Shader/VertexShader/VertexUV.hlsl", 1);
	PS = PixelShader::GetInstance(L"Shader/PixelShader/PixelUV.hlsl");
	CB = new ColourBuffer();

	nowMaxExp = round(pow((4 * (level + 1)),2.1f)) - round(pow((4 * level),2.1f));
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

void Player::UpdateDefault()
{
	// 공격 및 바라보는 방향은 Z키를 누르면 고정된다
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
	// atk dir arrow 초기화
	if (atk_arrow == nullptr)
	{
		atk_arrow = (Arrow*)(UIManager::Get()->GetUI(UI::UI_ID::ATK_ARROW));
		atk_arrow->SetTarget(this);
		atk_arrow->SetScale(Vector2(2, 2));
		atk_arrow->SetActive(true);
	}

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
		atk_arrow->rot.z = attack_dir.Angle();
	}
}

void Player::ChangeHP(float amount, Vector2 dir, Enemy* causer)
{
	if (amount > 0 && SkillManager::Get()->isHealDoubled)
	{
		HP += amount * 2.0f;
	}
	else
		HP += amount;

	// DmgText출력
	if (amount < 0)
	{
		int idx = 0;
		DmgText* ui = nullptr;
		Vector2 initPos(pos.x + ((is_looking_right) ? (-damageCollider->Size().x / 4.0f) : (damageCollider->Size().x / 4.0f))
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

void Player::GetExp(int expValue)
{
	nowExp += expValue * (1 + SkillManager::Get()->add_expRate);
	if (exp_bar == nullptr)
	{
		exp_bar = (ExpBar*)(UIManager::Get()->GetUI(UI::UI_ID::EXP_BAR));
		exp_bar->SetActive(true);
	}

	while(nowExp >= nowMaxExp)
	{
		nowExp -= nowMaxExp;
		level++;
		nowMaxExp = round(pow((4 * (level + 1)), 2.1f)) - round(pow((4 * level), 2.1f));
		// 레벨 업 시 이벤트 내용은 추후 추가
		
		UIManager::Get()->levelUpCnt++;
	}
	exp_bar->SetExpRate(nowExp / nowMaxExp);
}

bool Player::isCritical()
{
	int value = Random::Get()->GetRandomFloat(0.0f, 100.0f);
	if (value < crt)
		return true;
	else
		return false;
}
