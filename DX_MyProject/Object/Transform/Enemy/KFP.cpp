#include "framework.h"

KFP::KFP(ENEMY_NAME name, MOVE_TYPE type, Vector2 damgeSize, Vector2 attackSize)
	:Enemy(20.0f, 2.0f, 1.0f, 0.33f, 3)
	, damageSize(damageSize), attackSize(attackSize)
{
	wstring file = L"Textures/Enemy/PC Computer - HoloCure - Save the Fans - Myth Enemies EN Gen1_rm_bg.png";
	Texture* t = Texture::Add(file);

	// clips
	vector<Frame*> frames;

	// Takodachi clip
	frames.push_back(new Frame(file, 418.0f, 606.0f, 25.0f, 23.0f));
	frames.push_back(new Frame(file, 485.0f, 606.0f, 25.0f, 23.0f));
	frames.push_back(new Frame(file, 551.0f, 606.0f, 25.0f, 23.0f));

	clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP, 1.0f / 6.0f));
	frames.clear();

	// Hungry Takodachi Clip
	frames.push_back(new Frame(file, 418.0f, 672.0f, 25.0f, 23.0f));
	frames.push_back(new Frame(file, 485.0f, 672.0f, 25.0f, 23.0f));
	frames.push_back(new Frame(file, 551.0f, 672.0f, 25.0f, 23.0f));

	clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP, 1.0f / 6.0f));
	frames.clear();

	// collider
	damageColliders.push_back(new RectCollider(Vector2(50.0f, 46.0f)));
	damageCollider = damageColliders[0];
	atkColliders.push_back(new RectCollider(Vector2(25.0f, 23.0f)));
	attackCollider = atkColliders[0];

	// attackColliderOffset
	colliderOffset_table.push_back(Vector2(0.0f, 11.0f));
	damageCollider->pos = pos;
	attackCollider->pos = pos;
	colliderOffset_idx = 0;

	id = ENEMY_ID::KFP;

	is_active = false;
	for (auto c : damageColliders)
		c->SetActive(false);
	for (auto c : atkColliders)
		c->SetActive(false);

	SetEnemyName(name);
	// Respawn();
}

KFP::~KFP()
{
}

void KFP::Update()
{
	if (!is_active)return;

	Move();

	if (atk_nowTime < atk_delay)
		atk_nowTime += DELTA;

	UINT idx = (UINT)name - (UINT)ENEMY_NAME::KFP_EMPLOYEE;
	clips[idx]->Update();
	scale = clips[idx]->GetFrameSize() * attackCollider->Size() /
		clips[idx]->GetFrameOriginSize() * Vector2(2.0f, 2.0f);

	if (!is_looking_right)
	{
		scale = scale * Vector2(-1.0f, 1.0f);
	}
	if (badStatus_table[(UINT)BAD_STATUS::UPSIDE_DOWN]>0.0f)
	{
		badStatus_table[(UINT)BAD_STATUS::UPSIDE_DOWN] -= DELTA;
		scale = scale * Vector2(1.0f, -1.0f);
	}

	WorldUpdate();

	damageCollider->pos = pos;
	damageCollider->WorldUpdate();
	attackCollider->pos = pos + colliderOffset_table[colliderOffset_idx];
	attackCollider->WorldUpdate();

}

void KFP::Render()
{
	if (!is_active)return;

	VS->Set();
	PS->Set();

	WB->SetVS(0);
	CB->SetPS(0);

	UINT idx = (UINT)name - (UINT)ENEMY_NAME::KFP_EMPLOYEE;
	clips[idx]->Render();

	damageCollider->Render();
	attackCollider->Render();
}

void KFP::PostRender()
{
	switch (name)
	{
	case ENEMY_NAME::KFP_EMPLOYEE:
		ImGui::Text("KFP_EMPLOYEE ");
		break;
	case ENEMY_NAME::DISGRUNTLED_EMPLOYEE:
		ImGui::Text("DISGRUNTLED_EMPLOYEE ");
		break;
	default:
		break;
	}

	ImGui::Text("%f / %f", HP, MaxHP);
	ImGui::Text("pos : %f , %f", pos.x, pos.y);
}

void KFP::GetDamage(float damage)
{
	HP -= damage;

	if (HP <= 0.0f)
	{
		is_active = false;
		EnemySpawner::Get()->EnemyDead();
		ItemSpawner::Get()->GenerateItem(pos, Item::ITEM_ID::EXP, drop_exp);
	}
}

void KFP::Attack()
{
	if (!is_active)return;

	atk_nowTime = 0.0f;
	player->GetDamge(attack);
}

void KFP::SetEnemyName(ENEMY_NAME name) // type과 move_dir은 Enemy_Spwaner에서 활성 시 지정하도록 변경할 예정
{
	this->name = name;
	switch (name)
	{
	case ENEMY_NAME::KFP_EMPLOYEE:
	{
		SetStatus(20.0f, 2.0f, 1.0f, 0.33f, 3);
		type = MOVE_TYPE::STRAIGHT;
	}
	break;
	case ENEMY_NAME::DISGRUNTLED_EMPLOYEE:
	{
		SetStatus(50.0f, 4.0f, 1.15f, 0.33f, 7);
		type = MOVE_TYPE::STRAIGHT;
	}
	break;
	default:
		break;
	}
}