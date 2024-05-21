#include "framework.h"

Investi::Investi(ENEMY_NAME name, MOVE_TYPE type, Vector2 damgeSize, Vector2 attackSize)
	:Enemy(20.0f, 2.0f, 1.0f, 0.33f, 3)
	, damageSize(damageSize), attackSize(attackSize)
{
	wstring file = L"Textures/Enemy/PC Computer - HoloCure - Save the Fans - Myth Enemies EN Gen1_rm_bg.png";
	Texture* t = Texture::Add(file);

	// clips
	vector<Frame*> frames;

	// Investi Gator clip
	frames.push_back(new Frame(file, 607.0f, 81.0f, 45.0f, 32.0f));
	frames.push_back(new Frame(file, 673.0f, 81.0f, 45.0f, 32.0f));
	frames.push_back(new Frame(file, 739.0f, 81.0f, 45.0f, 32.0f));

	clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP, 1.0f / 6.0f));
	frames.clear();

	// Thicc Bubba Clip
	frames.push_back(new Frame(file, 617.0f, 203.0f, 33.0f, 43.0f));
	frames.push_back(new Frame(file, 684.0f, 203.0f, 33.0f, 43.0f));
	frames.push_back(new Frame(file, 746.0f, 203.0f, 33.0f, 43.0f));

	clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP, 1.0f / 6.0f));
	frames.clear();

	// collider
	damageColliders.push_back(new RectCollider(Vector2(66.0f, 86.0f)));
	damageCollider = damageColliders[0];
	atkColliders.push_back(new RectCollider(Vector2(33.0f, 43.0f)));
	attackCollider = atkColliders[0];

	// attackColliderOffset
	colliderOffset_table.push_back(Vector2(0.0f, 11.0f));
	damageCollider->pos = pos;
	attackCollider->pos = pos;
	colliderOffset_idx = 0;

	id = ENEMY_ID::INVESTI;

	is_active = false;
	for (auto c : damageColliders)
		c->SetActive(false);
	for (auto c : atkColliders)
		c->SetActive(false);

	SetEnemyName(name);
	// Respawn();
}

Investi::~Investi()
{
}

void Investi::Update()
{
	if (!is_active)return;

	Move();

	if (atk_nowTime < atk_delay)
		atk_nowTime += DELTA;

	UINT idx = (UINT)name - (UINT)ENEMY_NAME::INVESTI_GATOR;
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

void Investi::Render()
{
	if (!is_active)return;

	VS->Set();
	PS->Set();

	WB->SetVS(0);
	CB->SetPS(0);

	UINT idx = (UINT)name - (UINT)ENEMY_NAME::INVESTI_GATOR;
	clips[idx]->Render();

	damageCollider->Render();
	attackCollider->Render();
}

void Investi::PostRender()
{
	switch (name)
	{
	case ENEMY_NAME::INVESTI_GATOR:
		ImGui::Text("KFP_EMPLOYEE ");
		break;
	case ENEMY_NAME::THICC_BUBBA:
		ImGui::Text("THICC_BUBBA ");
		break;
	default:
		break;
	}

	ImGui::Text("%f / %f", HP, MaxHP);
	ImGui::Text("pos : %f , %f", pos.x, pos.y);
}

void Investi::GetDamage(float damage)
{
	HP -= damage;

	if (HP <= 0.0f)
	{
		is_active = false;
		EnemySpawner::Get()->EnemyDead();
		ItemSpawner::Get()->GenerateItem(pos, Item::ITEM_ID::EXP, drop_exp);
	}
}

void Investi::Attack()
{
	if (!is_active)return;

	atk_nowTime = 0.0f;
	player->GetDamge(attack);
}

void Investi::SetEnemyName(ENEMY_NAME name) // type과 move_dir은 Enemy_Spwaner에서 활성 시 지정하도록 변경할 예정
{
	this->name = name;
	switch (name)
	{
	case ENEMY_NAME::INVESTI_GATOR:
	{
		SetStatus(180.0f, 7.0f, 0.85f, 0.33f, 9);
		type = MOVE_TYPE::CHASE;
	}
	break;
	case ENEMY_NAME::THICC_BUBBA:
	{
		SetStatus(1000.0f, 12.0f, 0.85f, 0.33f, 20);
		type = MOVE_TYPE::CHASE;
	}
	break;
	default:
		break;
	}
}