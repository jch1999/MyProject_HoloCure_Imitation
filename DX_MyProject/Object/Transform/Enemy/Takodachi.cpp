#include "framework.h"

Takodachi::Takodachi(ENEMY_NAME name, MOVE_TYPE type, Vector2 damgeSize, Vector2 attackSize)
	:Enemy(80.0f, 4.0f, 0.4f, 0.33f, 8)
	, damageSize(damageSize), attackSize(attackSize)
{
	wstring file = L"Textures/Enemy/PC Computer - HoloCure - Save the Fans - Myth Enemies EN Gen1_rm_bg.png";
	Texture* t = Texture::Add(file);

	// clips
	vector<Frame*> frames;

	// Takodachi clip
	frames.push_back(new Frame(file, 623.0f, 379.0f, 21.0f, 21.0f));
	frames.push_back(new Frame(file, 688.0f, 379.0f, 21.0f, 21.0f));
	frames.push_back(new Frame(file, 754.0f, 379.0f, 21.0f, 21.0f));

	clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP, 1.0f / 6.0f));
	frames.clear();

	// Hungry Takodachi Clip
	frames.push_back(new Frame(file, 623.0f, 445.0f, 21.0f, 21.0f));
	frames.push_back(new Frame(file, 688.0f, 445.0f, 21.0f, 21.0f));
	frames.push_back(new Frame(file, 754.0f, 445.0f, 21.0f, 21.0f));

	clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP, 1.0f / 6.0f));
	frames.clear();

	// Tako Viking Clip
	frames.push_back(new Frame(file, 623.0f, 509.0f, 21.0f, 21.0f));
	frames.push_back(new Frame(file, 688.0f, 509.0f, 21.0f, 21.0f));
	frames.push_back(new Frame(file, 754.0f, 509.0f, 21.0f, 21.0f));

	clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP, 1.0f / 6.0f));
	frames.clear();

	// collider
	damageColliders.push_back(new RectCollider(Vector2(42.0f, 42.0f)));
	damageCollider = damageColliders[0];
	atkColliders.push_back(new RectCollider(Vector2(21.0f, 21.0f)));
	attackCollider = atkColliders[0];

	// attackColliderOffset
	colliderOffset_table.push_back(Vector2(0.0f, 10.5f));
	damageCollider->pos = pos;
	attackCollider->pos = pos;
	colliderOffset_idx = 0;

	id = ENEMY_ID::TAKODACHI;

	is_active = false;
	for (auto c : damageColliders)
		c->SetActive(false);
	for (auto c : atkColliders)
		c->SetActive(false);

	SetEnemyName(name);
	// Respawn();
}

Takodachi::~Takodachi()
{
}

void Takodachi::Update()
{
	if (!is_active)return;

	Move();

	if (atk_nowTime < atk_delay)
		atk_nowTime += DELTA;

	UINT idx = (UINT)name - (UINT)ENEMY_NAME::TAKODACHI;
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

void Takodachi::Render()
{
	if (!is_active)return;

	VS->Set();
	PS->Set();

	WB->SetVS(0);
	CB->SetPS(0);

	UINT idx = (UINT)name - (UINT)ENEMY_NAME::TAKODACHI;
	clips[idx]->Render();

	damageCollider->Render();
	attackCollider->Render();
}

void Takodachi::PostRender()
{
	switch (name)
	{
	case ENEMY_NAME::TAKODACHI:
		ImGui::Text("TAKODACHI ");
		break;
	case ENEMY_NAME::HUNGRY_TAKODACHI:
		ImGui::Text("HUNGRY_TAKODACHI ");
		break;
	case ENEMY_NAME::TAKO_VIKING:
		ImGui::Text("TAKO_VIKING ");
		break;
	default:
		break;
	}

	ImGui::Text("%f / %f", HP, MaxHP);
	ImGui::Text("pos : %f , %f", pos.x, pos.y);
}

void Takodachi::SetEnemyName(ENEMY_NAME name) // type과 move_dir은 Enemy_Spwaner에서 활성 시 지정하도록 변경할 예정
{
	this->name = name;
	switch (name)
	{
	case ENEMY_NAME::TAKODACHI:
	{
		SetStatus(80.0f, 4.0f, 0.4f, 0.33f, 8);
		type = MOVE_TYPE::CHASE;
	}
	break;
	case ENEMY_NAME::HUNGRY_TAKODACHI:
	{
		SetStatus(220.0f, 8.0f, 0.65f, 0.33f, 9);
		type = MOVE_TYPE::CHASE;
	}
	break;
	case ENEMY_NAME::TAKO_VIKING:
	{
		SetStatus(650.0f, 14.0f, 0.7f, 0.33f, 12);
		type = MOVE_TYPE::STRAIGHT;
	}
	break;
	default:
		break;
	}
}