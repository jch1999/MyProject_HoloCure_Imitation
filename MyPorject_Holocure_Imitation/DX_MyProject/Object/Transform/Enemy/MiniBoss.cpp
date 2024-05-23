#include "framework.h"

MiniBoss::MiniBoss(ENEMY_NAME name, MOVE_TYPE type)
	:Enemy(600.0f, 6.0f, 0.5f, 0.33f, 150)
{
	wstring file = L"Textures/Enemy/PC Computer - HoloCure - Save the Fans - Myth Enemies EN Gen1_rm_bg.png";
	Texture* t = Texture::Add(file);

	// clips
	vector<Frame*> frames;

	// Mega Shrimp
	frames.push_back(new Frame(file, 53.0f, 150.0f, 33.0f, 28.0f));
	frames.push_back(new Frame(file, 181.0f, 150.0f, 33.0f, 28.0f));
	frames.push_back(new Frame(file, 312.0f, 150.0f, 33.0f, 28.0f));

	clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP, 1.0f / 6.0f));
	frames.clear();

	// Tako Grande
	frames.push_back(new Frame(file, 623.0f, 379.0f, 21.0f, 21.0f));
	frames.push_back(new Frame(file, 688.0f, 381.0f, 21.0f, 21.0f));
	frames.push_back(new Frame(file, 755.0f, 380.0f, 21.0f, 21.0f));
	
	clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP, 1.0f / 6.0f));
	frames.clear();

	// Mega Dark Shrimp
	frames.push_back(new Frame(file, 53.0f, 280.0f, 33.0f, 28.0f));
	frames.push_back(new Frame(file, 181.0f, 280.0f, 33.0f, 28.0f));
	frames.push_back(new Frame(file, 312.0f, 280.0f, 33.0f, 28.0f));

	clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP, 1.0f / 6.0f));
	frames.clear();

	// Giant DeadBatter
	frames.push_back(new Frame(file, 418.0f, 135.0f, 33.0f, 45.0f));
	frames.push_back(new Frame(file, 485.0f, 135.0f, 33.0f, 45.0f));
	frames.push_back(new Frame(file, 548.0f, 135.0f, 33.0f, 45.0f));

	clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP, 1.0f / 6.0f));
	frames.clear();

	// Giant Q DeadBeat
	frames.push_back(new Frame(file, 418.0f, 333.0f, 34.0f, 45.0f));
	frames.push_back(new Frame(file, 484.0f, 333.0f, 34.0f, 45.0f));
	frames.push_back(new Frame(file, 548.0f, 333.0f, 34.0f, 45.0f));

	clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP, 1.0f / 6.0f));
	frames.clear();

	// Mega Q Shrimp
	frames.push_back(new Frame(file, 53.0f, 410.0f, 39.0f, 28.0f));
	frames.push_back(new Frame(file, 181.0f, 410.0f, 39.0f, 28.0f));
	frames.push_back(new Frame(file, 312.0f, 410.0f, 39.0f, 28.0f));

	clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP, 1.0f / 6.0f));
	frames.clear();
	
	
	// collider
	// Mega Shrimp & Mega Dark Shrimp
	damageColliders.push_back(new RectCollider(Vector2(65.0f, 62.0f)*2.0f));
	atkColliders.push_back(new RectCollider(Vector2(48.0f, 28.0f)*2.0f));
	// Tako Grande
	damageColliders.push_back(new RectCollider(Vector2(42.0f, 42.0f) * 3.0f));
	atkColliders.push_back(new RectCollider(Vector2(28.0f, 21.0f) * 3.0f));
	// Giant DeadBatter
	damageColliders.push_back(new RectCollider(Vector2(60.0f, 58.0f) * 2.0f));
	atkColliders.push_back(new RectCollider(Vector2(48.0f, 33.0f) * 2.0f));
	// Giant Q DeadBeat
	damageColliders.push_back(new RectCollider(Vector2(60.0f, 58.0f) * 2.0f));
	atkColliders.push_back(new RectCollider(Vector2(48.0f, 33.0f) * 2.0f));
	// Mega Q Shrimp
	damageColliders.push_back(new RectCollider(Vector2(70.0f, 62.0f) * 2.0f));
	atkColliders.push_back(new RectCollider(Vector2(52.8f, 28.0f) * 2.0f));

	// colliderOffset idx
	// Mega Shrimp & Mega Dark Shrimp & Mega Q Shrimp
	colliderOffset_table.push_back(Vector2(0.0f, 12.5f * 2.0f));
	// Tako Grande
	colliderOffset_table.push_back(Vector2(0.0f, 9.0f * 3.0f));
	// Giant DeadBatter & Giant Q DeadBeat 
	colliderOffset_table.push_back(Vector2(0.0f, 15.0f * 2.0f));

	damageCollider = damageColliders[0];
	attackCollider = atkColliders[0];

	id = Enemy::ENEMY_ID::MINI_BOSS;
	SetEnemyName(Enemy::ENEMY_NAME::MEGA_SHRIMP);

	is_active = false;
	damageCollider->SetActive(false);
	attackCollider->SetActive(false);
}

MiniBoss::~MiniBoss()
{
}

void MiniBoss::Update()
{
	if (!is_active)return;

	Move();

	if (atk_nowTime < atk_delay)
		atk_nowTime += DELTA;

	UINT idx = (UINT)name - (UINT)ENEMY_NAME::MEGA_SHRIMP;
	clips[idx]->Update();
	scale = clips[idx]->GetFrameSize() * attackCollider->Size() /
		clips[idx]->GetFrameOriginSize() * Vector2(1.5f, 2.0f);

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

void MiniBoss::Render()
{
	if (!is_active)return;

	VS->Set();
	PS->Set();

	WB->SetVS(0);
	CB->SetPS(0);

	UINT idx = (UINT)name - (UINT)ENEMY_NAME::MEGA_SHRIMP;
	clips[idx]->Render();

	damageCollider->Render();
	attackCollider->Render();
}

void MiniBoss::PostRender()
{
	switch (name)
	{
	case DeadBeat::ENEMY_NAME::MEGA_SHRIMP:
		ImGui::Text("MEGA_SHRIMP ");
		break;
	case DeadBeat::ENEMY_NAME::TAKO_GRANDE:
		ImGui::Text("TAKO_GRANDE ");
		break;
	case DeadBeat::ENEMY_NAME::MEGA_DARK_SHRIMP:
		ImGui::Text("MEGA_DARK_SHRIMP ");
		break;
	case DeadBeat::ENEMY_NAME::GIANT_DEADBATTER:
		ImGui::Text("GIANT_DEADBATTER ");
		break;
	case DeadBeat::ENEMY_NAME::GIANT_Q_DEADBEAT:
		ImGui::Text("GIANT_Q_DEADBEAT ");
		break;
	case DeadBeat::ENEMY_NAME::MEGA_Q_SHRIMP:
		ImGui::Text("MEGA_Q_SHRIMP ");
		break;
	default:
		break;
	}

	ImGui::Text("%f / %f", HP, MaxHP);
	ImGui::Text("pos : %f , %f", pos.x, pos.y);
}

void MiniBoss::SetEnemyName(ENEMY_NAME name)
{
	if (this->name == name)return;

	this->name = name;
	UINT idx = (UINT)name - (UINT)ENEMY_NAME::MEGA_SHRIMP;
	switch (name)
	{
	case ENEMY_NAME::MEGA_SHRIMP:
	{
		SetStatus(600.0f, 6.0f, 0.5f, 0.33f, 150);
		damageCollider->SetActive(false);
		damageCollider = damageColliders[0];
		attackCollider->SetActive(false);
		attackCollider = atkColliders[0];
		colliderOffset_idx = 0;
	}
		break;
	case ENEMY_NAME::TAKO_GRANDE:
	{
		SetStatus(1800.0f, 10.0f, 0.75f, 0.33f, 600);
		damageCollider->SetActive(false);
		damageCollider = damageColliders[1];
		attackCollider->SetActive(false);
		attackCollider = atkColliders[1];
		colliderOffset_idx = 1;
	}
		break;
	case ENEMY_NAME::MEGA_DARK_SHRIMP:
	{
		SetStatus(2500.0f, 10.0f, 0.9f, 0.33f, 1000);
		damageCollider->SetActive(false);
		damageCollider = damageColliders[0];
		attackCollider->SetActive(false);
		attackCollider = atkColliders[0];
		colliderOffset_idx = 0;
	}
		break;
	case ENEMY_NAME::GIANT_DEADBATTER:
	{
		SetStatus(3500.0f, 11.0f, 1.1f, 0.33f, 1500);
		damageCollider->SetActive(false);
		damageCollider = damageColliders[2];
		attackCollider->SetActive(false);
		attackCollider = atkColliders[2];
		colliderOffset_idx = 2;
	}
		break;
	case ENEMY_NAME::GIANT_Q_DEADBEAT:
	{
		SetStatus(7500.0f, 20.0f, 1.1f, 0.33f, 1200);
		damageCollider->SetActive(false);
		damageCollider = damageColliders[3];
		attackCollider->SetActive(false);
		attackCollider = atkColliders[3];
		colliderOffset_idx = 2;
	}
		break;
	case ENEMY_NAME::MEGA_Q_SHRIMP:
	{
		SetStatus(7500.0f, 20.0f, 1.1f, 0.33f, 1200);
		damageCollider->SetActive(false);
		damageCollider = damageColliders[4];
		attackCollider->SetActive(false);
		attackCollider = atkColliders[4];
		colliderOffset_idx = 0;
	}
		break;
	default:
		break;
	}

	damageCollider->SetActive(true);
	attackCollider->SetActive(true);
	type = MOVE_TYPE::CHASE;
}
