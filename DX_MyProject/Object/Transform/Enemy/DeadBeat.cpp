#include "framework.h"

vector<vector<shared_ptr<const Frame>>>& DeadBeat::GetDeadBeatFrames()
{
	static vector<vector<shared_ptr<const Frame>>> deadBeatFrames;
	return deadBeatFrames;
}

int& DeadBeat::GetDeadBestSpawnCnt()
{
	static int deadBeatSpawnCnt = 0;
	return deadBeatSpawnCnt;
}

DeadBeat::DeadBeat(ENEMY_NAME name, MOVE_TYPE type, Vector2 damgeSize, Vector2 attackSize)
	:Enemy(40.0f, 4.0f, 0.4f, 0.33f, 7)
	, damageSize(damageSize), attackSize(attackSize)
{
	if (GetDeadBeatFrames().empty())
	{
		InitFrame();
	}

	// clips
	auto& deadBeatFrames = GetDeadBeatFrames();
	for (auto& frame: deadBeatFrames)
	{
		clips.emplace_back(make_shared<Clip>(frame, Clip::CLIP_TYPE::LOOP, 1.0f / 6.0f));
	}

	// collider
	damageColliders.emplace_back(new RectCollider(Vector2(60.0f,58.0f)));
	damageCollider = damageColliders[0];
	atkColliders.emplace_back(new RectCollider(Vector2(50.0f, 30.0f)));
	atkColliders.emplace_back(new RectCollider(Vector2(60.0f,33.0f)));
	attackCollider = atkColliders[0];

	// attackColliderOffset
	colliderOffsetTable.emplace_back(Vector2(0.0f, 15.0f));
	colliderOffsetTable.emplace_back(Vector2(0.0f, 16.5f));
	damageCollider->pos = pos;
	attackCollider->pos = pos;
	colliderOffsetIdx = 0;

	id = ENEMY_ID::DEAD_BEAT;

	is_active = false;
	for (auto c : damageColliders)
		c->SetActive(false);
	for (auto c : atkColliders)
		c->SetActive(false);
	
	SetEnemyName(name);
	// Respawn();

	++GetDeadBestSpawnCnt();
}

DeadBeat::~DeadBeat()
{
	if ((--GetDeadBestSpawnCnt()) == 0)
	{
		ClearFrame();
	}
}

void DeadBeat::Update()
{
	if (!is_active)return;

	Move();

	if (atkNowTime < atkDelay)
		atkNowTime += DELTA;

	UINT idx = (UINT)name - (UINT)ENEMY_NAME::DEADBEAT;
	clips[idx]->Update();
	scale = clips[idx]->GetFrameSize() * attackCollider->Size() /
		clips[idx]->GetFrameOriginSize() * Vector2(1.2f, 2.0f);

	if (!isLookingRight)
	{
		scale = scale * Vector2(-1.0f, 1.0f);
	}
	if (badStatusTable[(UINT)BAD_STATUS::UPSIDE_DOWN]>0.f)
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

void DeadBeat::Render()
{
	if (!is_active)return;

	VS->Set();
	PS->Set();

	WB->SetVS(0);
	CB->SetPS(0);

	UINT idx = (UINT)name - (UINT)ENEMY_NAME::DEADBEAT;
	clips[idx]->Render();

	damageCollider->Render();
	attackCollider->Render();
}

void DeadBeat::PostRender()
{
	switch (name)
	{
	case DeadBeat::ENEMY_NAME::DEADBEAT:
		ImGui::Text("DEADBEAT ");
		break;
	case DeadBeat::ENEMY_NAME::DEADBATTER:
		ImGui::Text("DEADBATTER ");
		break;
	case DeadBeat::ENEMY_NAME::Q_DEADBEAT_A:
		ImGui::Text("Q_DEADBEAT_A ");
		break;
	case DeadBeat::ENEMY_NAME::Q_DEADBEAT_B:
		ImGui::Text("Q_DEADBEAT_B ");
		break;
	case DeadBeat::ENEMY_NAME::RIOT_DEADBEAT:
		ImGui::Text("RIOT_DEADBEAT ");
		break;
	case DeadBeat::ENEMY_NAME::RIOT_Q_DEADBEAT:
		ImGui::Text("RIOT_Q_DEADBEAT ");
		break;
	default:
		break;
	}

	ImGui::Text("%f / %f", HP, MaxHP);
	ImGui::Text("pos : %f , %f", pos.x, pos.y);
}

void DeadBeat::InitFrame()
{
	auto& deadBeatFrames = GetDeadBeatFrames();
	if (!(deadBeatFrames.empty())) return;

	wstring file = L"Textures/Enemy/PC Computer - HoloCure - Save the Fans - Myth Enemies EN Gen1_rm_bg.png";

	// DeadBeat clip
	{
		vector<shared_ptr<const Frame>> NormalDeadBeatFrames;
		NormalDeadBeatFrames.emplace_back(make_shared<const Frame>(file, 419.0f, 80.0f, 28.0f, 34.0f));
		NormalDeadBeatFrames.emplace_back(make_shared<const Frame>(file, 485.0f, 79.0f, 28.0f, 35.0f));
		NormalDeadBeatFrames.emplace_back(make_shared<const Frame>(file, 550.0f, 81.0f, 28.0f, 35.0f));
		deadBeatFrames.push_back(NormalDeadBeatFrames);
	}
	// DeadBatter Clip
	{
		vector<shared_ptr<const Frame>> DeadBatterFrames;
		DeadBatterFrames.emplace_back(make_shared<const Frame>(file, 418.0f, 135.0f, 33.0f, 45.0f));
		DeadBatterFrames.emplace_back(make_shared<const Frame>(file, 485.0f, 135.0f, 33.0f, 45.0f));
		DeadBatterFrames.emplace_back(make_shared<const Frame>(file, 548.0f, 135.0f, 33.0f, 45.0f));
		deadBeatFrames.push_back(DeadBatterFrames);
	}
	// Q DeadBeat A Clip
	{
		vector<shared_ptr<const Frame>> QDeadBeatAFrames;
		QDeadBeatAFrames.emplace_back(make_shared<const Frame>(file, 418.0f, 267.0f, 34.0f, 45.0f));
		QDeadBeatAFrames.emplace_back(make_shared<const Frame>(file, 484.0f, 267.0f, 34.0f, 45.0f));
		QDeadBeatAFrames.emplace_back(make_shared<const Frame>(file, 548.0f, 267.0f, 34.0f, 45.0f));
		deadBeatFrames.push_back(QDeadBeatAFrames);
	}
	// Q DeadBeat B Clip
	{
		vector<shared_ptr<const Frame>> QDeadBeatBFrames;
		QDeadBeatBFrames.emplace_back(make_shared<const Frame>(file, 418.0f, 333.0f, 34.0f, 45.0f));
		QDeadBeatBFrames.emplace_back(make_shared<const Frame>(file, 484.0f, 333.0f, 34.0f, 45.0f));
		QDeadBeatBFrames.emplace_back(make_shared<const Frame>(file, 548.0f, 333.0f, 34.0f, 45.0f));
		deadBeatFrames.push_back(QDeadBeatBFrames);
	}
	// Riot DeadBeat Clip
	{
		vector<shared_ptr<const Frame>> RiotDeadBatterFrames;
		RiotDeadBatterFrames.emplace_back(make_shared<const Frame>(file, 419.0f, 409.0f, 32.0f, 35.0f));
		RiotDeadBatterFrames.emplace_back(make_shared<const Frame>(file, 485.0f, 409.0f, 32.0f, 35.0f));
		RiotDeadBatterFrames.emplace_back(make_shared<const Frame>(file, 550.0f, 409.0f, 32.0f, 35.0f));
		deadBeatFrames.push_back(RiotDeadBatterFrames);
	}
	// Riot Q DeadBeat Clip
	{
		vector<shared_ptr<const Frame>> RiotQDeadBatterFrames;
		RiotQDeadBatterFrames.emplace_back(make_shared<const Frame>(file, 419.0f, 475.0f, 36.0f, 33.0f));
		RiotQDeadBatterFrames.emplace_back(make_shared<const Frame>(file, 484.0f, 475.0f, 36.0f, 33.0f));
		RiotQDeadBatterFrames.emplace_back(make_shared<const Frame>(file, 549.0f, 477.0f, 36.0f, 33.0f));
		deadBeatFrames.push_back(RiotQDeadBatterFrames);
	}
}

void DeadBeat::ClearFrame()
{
	GetDeadBeatFrames().clear();
}

void DeadBeat::SetEnemyName(ENEMY_NAME name) // type과 move_dir은 Enemy_Spwaner에서 활성 시 지정하도록 변경할 예정
{
	this->name = name;
	switch (name)
	{
	case DeadBeat::ENEMY_NAME::DEADBEAT:
	{
		SetStatus(40.0f, 4.0f, 0.4f, 0.33f, 7);
		attackCollider->SetActive(false);
		attackCollider = atkColliders[0];
		colliderOffsetIdx = 0;
		attackCollider->SetActive(true);
		type = MOVE_TYPE::CHASE;
	}
	break;
	case DeadBeat::ENEMY_NAME::DEADBATTER:
	{
		SetStatus(150.0f, 7.0f, 0.6f, 0.33f, 9);
		attackCollider->SetActive(false);
		attackCollider = atkColliders[1];
		colliderOffsetIdx = 1;
		attackCollider->SetActive(true);
		type = MOVE_TYPE::CHASE;
	}
	break;
	case DeadBeat::ENEMY_NAME::Q_DEADBEAT_A:
	case DeadBeat::ENEMY_NAME::Q_DEADBEAT_B:
	{
		SetStatus(650.0f, 14.0f, 0.7f, 0.33f, 12);
		attackCollider->SetActive(false);
		attackCollider = atkColliders[1];
		colliderOffsetIdx = 1;
		attackCollider->SetActive(true);
		type = MOVE_TYPE::CHASE;
	}
	break;
	case DeadBeat::ENEMY_NAME::RIOT_DEADBEAT:
	{
		SetStatus(1000.0f, 4.0f, 160.0f, 0.33f, 7);
		attackCollider->SetActive(false);
		attackCollider = atkColliders[0];
		colliderOffsetIdx = 1;
		attackCollider->SetActive(true);
		SetMoveDir(Vector2(1.0f, 0.0f));
		type = MOVE_TYPE::STRAIGHT;
	}
	break;
	case DeadBeat::ENEMY_NAME::RIOT_Q_DEADBEAT:
	{
		SetStatus(2000.0f, 4.0f, 200.0f, 0.33f, 10);
		attackCollider->SetActive(false);
		attackCollider = atkColliders[1];
		colliderOffsetIdx = 1;
		attackCollider->SetActive(true);
		SetMoveDir(Vector2(1.0f, 0.0f));
		type = MOVE_TYPE::STRAIGHT;
	}
	break;
	default:
		break;
	}
}