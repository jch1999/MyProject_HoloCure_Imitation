#include "framework.h"

vector<vector<shared_ptr<const Frame>>> BloomGloom::bloomGloomFrames;
int BloomGloom::bloomGloomSpawnCnt = 0;

BloomGloom::BloomGloom(ENEMY_NAME name, MOVE_TYPE type, Vector2 damgeSize, Vector2 attackSize)
	:Enemy(8.0f, 2.0f, 0.35f, 0.33f, 7)
	, damageSize(damageSize), attackSize(attackSize)
{
	if (bloomGloomFrames.empty())
	{
		InitFrame();
	}

	// clips
	for (auto& frames : bloomGloomFrames)
	{
		clips.emplace_back(make_shared<Clip>(frames, Clip::CLIP_TYPE::LOOP, 1.0f / 6.0f));
	}
	
	// collider
	damageColliders.emplace_back(new RectCollider(Vector2(50.0f, 46.0f)));
	damageCollider = damageColliders[0];
	atkColliders.emplace_back(new RectCollider(Vector2(25.0f, 23.0f)));
	attackCollider = atkColliders[0];

	// attackColliderOffset
	colliderOffsetTable.emplace_back(Vector2(0.0f, 11.0f));
	damageCollider->pos = pos;
	attackCollider->pos = pos;
	colliderOffsetIdx = 0;

	id = ENEMY_ID::BLOOM_GLOOM;

	is_active = false;
	for (auto c : damageColliders)
		c->SetActive(false);
	for (auto c : atkColliders)
		c->SetActive(false);

	SetEnemyName(name);
	// Respawn();

	++bloomGloomSpawnCnt;
}

BloomGloom::~BloomGloom()
{
	if ((--bloomGloomSpawnCnt) == 0)
	{
		ClearFrame();
	}
}

void BloomGloom::Update()
{
	if (!is_active)return;

	Move();

	if (atkNowTime < atkDelay)
		atkNowTime += DELTA;

	UINT idx = (UINT)name - (UINT)ENEMY_NAME::BLOOM;
	clips[idx]->Update();
	scale = clips[idx]->GetFrameSize() * attackCollider->Size() /
		clips[idx]->GetFrameOriginSize() * Vector2(2.0f, 2.0f);

	if (!isLookingRight)
	{
		scale = scale * Vector2(-1.0f, 1.0f);
	}
	if (badStatusTable[(UINT)BAD_STATUS::UPSIDE_DOWN]>0.0f)
	{
		badStatusTable[(UINT)BAD_STATUS::UPSIDE_DOWN] -= DELTA;
		scale = scale * Vector2(1.0f, -1.0f);
	}

	WorldUpdate();

	damageCollider->pos = pos;
	damageCollider->WorldUpdate();
	attackCollider->pos = pos + colliderOffsetTable[colliderOffsetIdx];
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

void BloomGloom::InitFrame()
{
	if (!(bloomGloomFrames.empty())) return;

	wstring file = L"Textures/Enemy/PC Computer - HoloCure - Save the Fans - CouncilRyS Enemies EN Gen2 Hope_rm_bg.png";

	// Bloom clip
	{
		vector<shared_ptr<const Frame>> bloomFrames;
		bloomFrames.emplace_back(make_shared<const Frame>(file, 18.0f, 288.0f, 28.0f, 25.0f));
		bloomFrames.emplace_back(make_shared<const Frame>(file, 84.0f, 288.0f, 28.0f, 25.0f));
		bloomFrames.emplace_back(make_shared<const Frame>(file, 151.0f, 288.0f, 28.0f, 25.0f));
		bloomGloomFrames.push_back(bloomFrames);
	}
	// Gloom Clip
	{
		vector<shared_ptr<const Frame>> gloomFrames;
		gloomFrames.emplace_back(make_shared<const Frame>(file, 18.0f, 354.0f, 28.0f, 25.0f));
		gloomFrames.emplace_back(make_shared<const Frame>(file, 84.0f, 354.0f, 28.0f, 25.0f));
		gloomFrames.emplace_back(make_shared<const Frame>(file, 151.0f, 354.0f, 28.0f, 25.0f));
		bloomGloomFrames.push_back(gloomFrames);
	}
}

void BloomGloom::ClearFrame()
{
	if (bloomGloomFrames.empty()) return;

	bloomGloomFrames.clear();
}

void BloomGloom::SetEnemyName(ENEMY_NAME name) // type과 moveDir은 Enemy_Spwaner에서 활성 시 지정하도록 변경할 예정
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