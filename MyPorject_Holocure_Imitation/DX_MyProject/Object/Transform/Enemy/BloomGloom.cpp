#include "framework.h"

BloomGloom::BloomGloom(ENEMY_NAME name, MOVE_TYPE type, Vector2 damgeSize, Vector2 attackSize)
	:Enemy(8.0f, 2.0f, 0.35f, 0.33f, 7)
	, damageSize(damageSize), attackSize(attackSize)
{
	wstring file = L"Textures/Enemy/PC Computer - HoloCure - Save the Fans - CouncilRyS Enemies EN Gen2 Hope_rm_bg.png";
	Texture* t = Texture::Add(file);

	// clips
	vector<Frame*> frames;

	// Bloom clip
	frames.push_back(new Frame(file, 18.0f, 288.0f, 28.0f, 25.0f));
	frames.push_back(new Frame(file, 84.0f, 288.0f, 28.0f, 25.0f));
	frames.push_back(new Frame(file, 151.0f, 288.0f, 28.0f, 25.0f));

	clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP, 1.0f / 6.0f));
	frames.clear();

	// Gloom Clip
	frames.push_back(new Frame(file, 18.0f, 354.0f, 28.0f, 25.0f));
	frames.push_back(new Frame(file, 84.0f, 354.0f, 28.0f, 25.0f));
	frames.push_back(new Frame(file, 151.0f, 354.0f, 28.0f, 25.0f));

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

	id = ENEMY_ID::BLOOM_GLOOM;

	is_active = false;
	for (auto c : damageColliders)
		c->SetActive(false);
	for (auto c : atkColliders)
		c->SetActive(false);

	SetEnemyName(name);
	// Respawn();
}

BloomGloom::~BloomGloom()
{
}

void BloomGloom::Update()
{
	if (!is_active)return;

	Move();

	if (atk_nowTime < atk_delay)
		atk_nowTime += DELTA;

	UINT idx = (UINT)name - (UINT)ENEMY_NAME::BLOOM;
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

void BloomGloom::Render()
{
	if (!is_active)return;

	VS->Set();
	PS->Set();

	WB->SetVS(0);
	CB->SetPS(0);

	UINT idx = (UINT)name - (UINT)ENEMY_NAME::BLOOM;
	clips[idx]->Render();

	damageCollider->Render();
	attackCollider->Render();
}

void BloomGloom::PostRender()
{
	switch (name)
	{
	case ENEMY_NAME::BLOOM:
		ImGui::Text("BLOOM ");
		break;
	case ENEMY_NAME::GLOOM:
		ImGui::Text("GLOOM ");
		break;
	default:
		break;
	}

	ImGui::Text("%f / %f", HP, MaxHP);
	ImGui::Text("pos : %f , %f", pos.x, pos.y);
}

void BloomGloom::SetEnemyName(ENEMY_NAME name) // type과 move_dir은 Enemy_Spwaner에서 활성 시 지정하도록 변경할 예정
{
	this->name = name;
	/*
	switch (name)
	{
	case ENEMY_NAME::BLOOM:
	{
		SetStatus(30.0f, 6.0f, 0.7f, 0.33f, 12);
		type = MOVE_TYPE::CHASE;
	}
	break;
	case ENEMY_NAME::GLOOM:
	{
		SetStatus(30.0f, 6.0f, 0.7f, 0.33f, 12);
		type = MOVE_TYPE::CHASE;
	}
	break;
	default:
		break;
	}
	*/
}