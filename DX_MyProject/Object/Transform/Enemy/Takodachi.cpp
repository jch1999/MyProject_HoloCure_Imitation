#include "framework.h"

vector<vector<shared_ptr<const Frame>>> Takodachi::takodachiFrames;
int Takodachi::takodachiSpawnCnt = 0;

Takodachi::Takodachi(ENEMY_NAME name, MOVE_TYPE type, Vector2 damgeSize, Vector2 attackSize)
	:Enemy(80.0f, 4.0f, 0.4f, 0.33f, 8)
	, damageSize(damageSize), attackSize(attackSize)
{
	if (takodachiFrames.empty())
	{
		InitFrame();
	}

	// clips
	for (auto& frames : takodachiFrames)
	{
		clips.emplace_back(make_shared<Clip>(frames, Clip::CLIP_TYPE::LOOP, 1.0f / 6.0f));
	}
	

	// collider
	damageColliders.emplace_back(new RectCollider(Vector2(42.0f, 42.0f)));
	damageCollider = damageColliders[0];
	atkColliders.emplace_back(new RectCollider(Vector2(21.0f, 21.0f)));
	attackCollider = atkColliders[0];

	// attackColliderOffset
	colliderOffsetTable.emplace_back(Vector2(0.0f, 10.5f));
	damageCollider->pos = pos;
	attackCollider->pos = pos;
	colliderOffsetIdx = 0;

	id = ENEMY_ID::TAKODACHI;

	is_active = false;
	for (auto c : damageColliders)
		c->SetActive(false);
	for (auto c : atkColliders)
		c->SetActive(false);

	SetEnemyName(name);
	// Respawn();

	++takodachiSpawnCnt;
}

Takodachi::~Takodachi()
{
	if ((--takodachiSpawnCnt) == 0)
	{
		ClearFrame();
	}
}

void Takodachi::Update()
{
	if (!is_active)return;

	Move();

	if (atkNowTime < atkDelay)
		atkNowTime += DELTA;

	UINT idx = (UINT)name - (UINT)ENEMY_NAME::TAKODACHI;
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

void Takodachi::InitFrame()
{
	if (!(takodachiFrames.empty())) return;

	wstring file = L"Textures/Enemy/PC Computer - HoloCure - Save the Fans - Myth Enemies EN Gen1_rm_bg.png";

	// Takodachi clip
	{
		vector<shared_ptr<const Frame>> normalTakdodachiFrames;
		normalTakdodachiFrames.emplace_back(make_shared<const Frame>(file, 623.0f, 379.0f, 21.0f, 21.0f));
		normalTakdodachiFrames.emplace_back(make_shared<const Frame>(file, 688.0f, 379.0f, 21.0f, 21.0f));
		normalTakdodachiFrames.emplace_back(make_shared<const Frame>(file, 754.0f, 379.0f, 21.0f, 21.0f));
		takodachiFrames.push_back(normalTakdodachiFrames);
	}
	// Hungry Takodachi Clip
	{
		vector<shared_ptr<const Frame>> hungryTakdodachiFrames;
		hungryTakdodachiFrames.emplace_back(make_shared<const Frame>(file, 623.0f, 445.0f, 21.0f, 21.0f));
		hungryTakdodachiFrames.emplace_back(make_shared<const Frame>(file, 688.0f, 445.0f, 21.0f, 21.0f));
		hungryTakdodachiFrames.emplace_back(make_shared<const Frame>(file, 754.0f, 445.0f, 21.0f, 21.0f));
		takodachiFrames.push_back(hungryTakdodachiFrames);
	}
	// Tako Viking Clip
	{
		vector<shared_ptr<const Frame>> takoVikingFrames;
		takoVikingFrames.emplace_back(make_shared<const Frame>(file, 623.0f, 509.0f, 21.0f, 21.0f));
		takoVikingFrames.emplace_back(make_shared<const Frame>(file, 688.0f, 509.0f, 21.0f, 21.0f));
		takoVikingFrames.emplace_back(make_shared<const Frame>(file, 754.0f, 509.0f, 21.0f, 21.0f));
		takodachiFrames.push_back(takoVikingFrames);
	}
}

void Takodachi::ClearFrame()
{
	if (takodachiFrames.empty()) return;

	takodachiFrames.clear();
}

void Takodachi::SetEnemyName(ENEMY_NAME name) // type과 moveDir은 Enemy_Spwaner에서 활성 시 지정하도록 변경할 예정
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