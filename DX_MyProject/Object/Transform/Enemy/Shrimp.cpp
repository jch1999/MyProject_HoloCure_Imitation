#include "framework.h"

Shrimp::Shrimp(ENEMY_NAME name, MOVE_TYPE type,Vector2 damgeSize, Vector2 attackSize)
	:Enemy(8.0f,2.0f,0.35f,0.33f,6)
	,damageSize(damageSize),attackSize(attackSize)
{
	wstring file=L"Textures/Enemy/PC Computer - HoloCure - Save the Fans - Myth Enemies EN Gen1_rm_bg.png";
	Texture* t = Texture::Add(file);

	// clips
	vector<Frame*> frames;

	// Shrimp clip
	frames.push_back(new Frame(file, 53.0f, 150.0f, 33.0f, 28.0f));
	frames.push_back(new Frame(file, 181.0f, 150.0f, 33.0f, 28.0f));
	frames.push_back(new Frame(file, 312.0f, 150.0f, 33.0f, 28.0f));

	clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP, 1.0f / 6.0f));
	frames.clear();

	// Dark Shrimp Clip
	frames.push_back(new Frame(file, 53.0f, 280.0f, 33.0f, 28.0f));
	frames.push_back(new Frame(file, 181.0f, 280.0f, 33.0f, 28.0f));
	frames.push_back(new Frame(file, 312.0f, 280.0f, 33.0f, 28.0f));

	clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP, 1.0f / 6.0f));
	frames.clear();

	// Q Shrimp A Clip
	frames.push_back(new Frame(file, 53.0f, 410.0f, 39.0f, 28.0f));
	frames.push_back(new Frame(file, 181.0f, 410.0f, 39.0f, 28.0f));
	frames.push_back(new Frame(file, 312.0f, 410.0f, 39.0f, 28.0f));

	clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP, 1.0f / 6.0f));
	frames.clear();

	// Q Shrimp B Clip
	frames.push_back(new Frame(file, 53.0f, 540.0f, 39.0f, 28.0f));
	frames.push_back(new Frame(file, 181.0f, 540.0f, 39.0f, 28.0f));
	frames.push_back(new Frame(file, 312.0f, 540.0f, 39.0f, 28.0f));

	clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP, 1.0f / 6.0f));
	frames.clear();

	// Riot Q Shrimp Clip
	frames.push_back(new Frame(file, 53.0f, 670.0f, 33.0f, 28.0f));
	frames.push_back(new Frame(file, 181.0f, 670.0f, 33.0f, 28.0f));
	frames.push_back(new Frame(file, 312.0f, 670.0f, 33.0f, 28.0f));

	clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP, 1.0f / 6.0f));
	frames.clear();

	// collider
	// dmg - Shrimp, Dark Shrimp, Riot Shrimp
	damageColliders.push_back(new RectCollider(Vector2(65.0f,62.0f)));
	// dmg -  Q Shrimp
	damageColliders.push_back(new RectCollider(Vector2(70.0f,62.0f)));
	damageCollider = damageColliders[0];
	
	// atk - Shrimp, Dark Shrimp, Riot Shrimp
	atkColliders.push_back(new RectCollider(Vector2(60.0f, 28.0f)));
	// atk -  Q Shrimp
	atkColliders.push_back(new RectCollider(Vector2(66.0f, 28.0f)));
	attackCollider = atkColliders[0];

	// attackColliderOffset
	colliderOffset_table.push_back(Vector2(0.0f, 14.0f));
	colliderOffset_idx = 0;

	is_active = false;
	for (auto c : atkColliders)
		c->SetActive(false);
	for (auto c : damageColliders)
		c->SetActive(false);

	damageCollider->pos = pos;
	attackCollider->pos = pos;

	id = ENEMY_ID::SHRIMP;
	
	// name에 따른 초기값 부여 -> ENemeySpawner에서 진행
	SetEnemyName(name);
	// Respawn();

}

Shrimp::~Shrimp()
{
}

void Shrimp::Update()
{
	if (!is_active)return;
	
	Move();
	
	if (atk_nowTime < atk_delay)
		atk_nowTime += DELTA;
	UINT idx = (UINT)name - (UINT)ENEMY_NAME::SHRIMP;
	clips[idx]->Update();
	scale = clips[idx]->GetFrameSize() * attackCollider->Size() /
		clips[idx]->GetFrameOriginSize() * Vector2(1.2, 2.0f);
	
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

void Shrimp::Render()
{
	if (!is_active)return;
	
	VS->Set();
	PS->Set();

	WB->SetVS(0);
	CB->SetPS(0);

	UINT idx = (UINT)name - (UINT)ENEMY_NAME::SHRIMP;
	clips[idx]->Render();

	damageCollider->Render();
	attackCollider->Render();
}

void Shrimp::PostRender()
{
	switch (name)
	{
	case Shrimp::ENEMY_NAME::SHRIMP:
		ImGui::Text("SHRIMP ");
		break;
	case Shrimp::ENEMY_NAME::DARKSHRIMP:
		ImGui::Text("DARKSHRIMP ");
		break;
	case Shrimp::ENEMY_NAME::Q_SHRIMP_A:
		ImGui::Text("Q_SHRIMP_A ");
		break;
	case Shrimp::ENEMY_NAME::Q_SHRIMP_B:
		ImGui::Text("Q_SHRIMP_B ");
		break;
	case Shrimp::ENEMY_NAME::RIOT_Q_SHRIMP:
		ImGui::Text("RIOT_Q_SHRIMP ");
		break;
	default:
		break;
	}
	ImGui::Text("%f / %f", HP, MaxHP);
	ImGui::Text("pos : %f , %f", pos.x,pos.y);
}

void Shrimp::SetEnemyName(ENEMY_NAME name)// type과 move_dir은 Enemy_Spwaner에서 활성 시 지정하도록 변경할 예정
{
	if (this->name == name)return; // 기존과 같다면 수정할 필요가 없음

	this->name = name;
	switch (name)
	{
	case Shrimp::ENEMY_NAME::SHRIMP:
	{
		SetStatus(8.0f, 2.0f, 0.35f, 0.33f, 6);
		damageCollider->SetActive(false);
		damageCollider = damageColliders[0];
		damageCollider->SetActive(true);

		attackCollider->SetActive(false);
		attackCollider = atkColliders[0];
		attackCollider->SetActive(true);
		type = MOVE_TYPE::CHASE;
	}
	break;
	case Shrimp::ENEMY_NAME::DARKSHRIMP:
	{
		SetStatus(125.0f, 5.0f, 0.6f, 0.33f, 12);
		damageCollider->SetActive(false);
		damageCollider = damageColliders[0];
		damageCollider->SetActive(true);

		attackCollider->SetActive(false);
		attackCollider = atkColliders[0];
		attackCollider->SetActive(true);
		type = MOVE_TYPE::CHASE;
	}
	break;
	case Shrimp::ENEMY_NAME::Q_SHRIMP_A:
	case Shrimp::ENEMY_NAME::Q_SHRIMP_B:
	{
		SetStatus(650.0f, 12.0f, 0.9f, 0.33f, 12);
		damageCollider->SetActive(false);
		damageCollider = damageColliders[1];
		damageCollider->SetActive(true);

		attackCollider->SetActive(false);
		attackCollider = atkColliders[1];
		attackCollider->SetActive(true);
		type = MOVE_TYPE::CHASE;
	}
	break;
	case Shrimp::ENEMY_NAME::RIOT_Q_SHRIMP:
	{
		SetStatus(2000.0f, 4.0f, 1.6f, 0.33f, 10);
		SetMoveDir(Vector2(1.0f, 0.0f));
		damageCollider->SetActive(false);
		damageCollider = damageColliders[0];
		damageCollider->SetActive(true);

		attackCollider->SetActive(false);
		attackCollider = atkColliders[0];
		attackCollider->SetActive(true);
		type = MOVE_TYPE::STRAIGHT;
	}
	break;
	default:
		break;
	}
}
