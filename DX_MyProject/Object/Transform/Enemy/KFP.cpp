#include "framework.h"

vector<vector<shared_ptr<const Frame>>> KFP::kfpFrames;
int KFP::kfpSpawnCnt = 0;

KFP::KFP(ENEMY_NAME name, MOVE_TYPE type, Vector2 damgeSize, Vector2 attackSize)
	:Enemy(20.0f, 2.0f, 1.0f, 0.33f, 3)
	, damageSize(damageSize), attackSize(attackSize)
{
	if (kfpFrames.empty())
	{
		InitFrame();
	}

	// clips
	for (auto& frames : kfpFrames)
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

	id = ENEMY_ID::KFP;

	is_active = false;
	for (auto c : damageColliders)
		c->SetActive(false);
	for (auto c : atkColliders)
		c->SetActive(false);

	SetEnemyName(name);
	// Respawn();

	++kfpSpawnCnt;
}

KFP::~KFP()
{
	if ((--kfpSpawnCnt) == 0)
	{
		ClearFrame();
	}
}

void KFP::Update()
{
	if (!is_active)return;

	Move();

	if (atkNowTime < atkDelay)
		atkNowTime += DELTA;

	UINT idx = (UINT)name - (UINT)ENEMY_NAME::KFP_EMPLOYEE;
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

void KFP::InitFrame()
{
	if (!(kfpFrames.empty())) return;

	wstring file = L"Textures/Enemy/PC Computer - HoloCure - Save the Fans - Myth Enemies EN Gen1_rm_bg.png";

	// KFP clip
	{
		vector<shared_ptr<const Frame>> normalKFPFrames;
		normalKFPFrames.emplace_back(make_shared<const Frame>(file, 418.0f, 606.0f, 25.0f, 23.0f));
		normalKFPFrames.emplace_back(make_shared<const Frame>(file, 485.0f, 606.0f, 25.0f, 23.0f));
		normalKFPFrames.emplace_back(make_shared<const Frame>(file, 551.0f, 606.0f, 25.0f, 23.0f));
		kfpFrames.push_back(normalKFPFrames);
	}
	// Angry KFP Clip
	{
		vector<shared_ptr<const Frame>> angryKFPFrames;
		angryKFPFrames.emplace_back(make_shared<const Frame>(file, 418.0f, 672.0f, 25.0f, 23.0f));
		angryKFPFrames.emplace_back(make_shared<const Frame>(file, 485.0f, 672.0f, 25.0f, 23.0f));
		angryKFPFrames.emplace_back(make_shared<const Frame>(file, 551.0f, 672.0f, 25.0f, 23.0f));
		kfpFrames.push_back(angryKFPFrames);
	}
}

void KFP::ClearFrame()
{
	if (kfpFrames.empty()) return;

	kfpFrames.clear();
}

void KFP::SetEnemyName(ENEMY_NAME name) // type과 moveDir은 Enemy_Spwaner에서 활성 시 지정하도록 변경할 예정
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