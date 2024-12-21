#include "framework.h"
#include "Baelz.h"

Baelz::Baelz(float MaxHP, float atk, float speed, float crt, float pickUpRange, float delay, Vector2 size)
	:Player(MaxHP, atk, speed, crt, pickUpRange, delay, 0, size)
{
	wstring file = L"Textures/Player/PC Computer - HoloCure - Save the Fans - Hakos Baelz_rm_bg.png";

	// clips
	vector<shared_ptr<const Frame>> frames;

	// PLAYER_STATUS::IDLE에 대응하는 애니메이션을 넣는 파트
	frames.push_back(make_shared<const Frame>(file, 21, 60, 36, 33));
	frames.push_back(make_shared<const Frame>(file, 87, 59, 35, 34));
	frames.push_back(make_shared<const Frame>(file, 149, 60, 37, 33));
	frames.push_back(make_shared<const Frame>(file, 214, 59, 38, 34));
	// 이를 Clip으로 만들어 clips에 저장
	AddClip(make_shared<Clip>(frames, Clip::CLIP_TYPE::LOOP, 1.0f / 4.5f));
	frames.clear();

	// PLAYER_STATUS::MOVE에 대응하는 애니메이션을 넣는 파트
	frames.push_back(make_shared<const Frame>(file, 23, 135, 36, 31));
	frames.push_back(make_shared<const Frame>(file, 86, 136, 38, 32));
	frames.push_back(make_shared<const Frame>(file, 151, 139, 38, 33));
	frames.push_back(make_shared<const Frame>(file, 218, 135, 36, 31));
	frames.push_back(make_shared<const Frame>(file, 281, 136, 38, 32));
	frames.push_back(make_shared<const Frame>(file, 346, 139, 38, 33));
	
	AddClip(make_shared<Clip>(frames, Clip::CLIP_TYPE::LOOP, 1.0f / 6.0f));
	frames.clear();

	// PLAYER_STATUS::IDLE_DAMAGED - IDLE과 동일
	frames.push_back(make_shared<const Frame>(file, 21, 60, 36, 33));
	frames.push_back(make_shared<const Frame>(file, 87, 59, 35, 34));
	frames.push_back(make_shared<const Frame>(file, 149, 60, 37, 33));
	frames.push_back(make_shared<const Frame>(file, 214, 59, 38, 34));
	AddClip(make_shared<Clip>(frames, Clip::CLIP_TYPE::LOOP, 1.0f / 4.5f));
	frames.clear();

	// PLAUER_STATUS::MOVE_DAMAGED - MOVE와 동일
	frames.push_back(make_shared<const Frame>(file, 23, 135, 36, 31));
	frames.push_back(make_shared<const Frame>(file, 86, 136, 38, 32));
	frames.push_back(make_shared<const Frame>(file, 151, 139, 38, 33));
	frames.push_back(make_shared<const Frame>(file, 218, 135, 36, 31));
	frames.push_back(make_shared<const Frame>(file, 281, 136, 38, 32));
	frames.push_back(make_shared<const Frame>(file, 346, 139, 38, 33));
	
	AddClip(make_shared<Clip>(frames, Clip::CLIP_TYPE::LOOP, 1.0f / 6.0f));
	frames.clear();


	damageCollider = new RectCollider(size);
	for (int i = 0; i < 20; i++)
	{
		CircleCollider* pickupCollider = new CircleCollider(defaultPickUpRange * (1.0f + 0.2f * i));
		pickupCollider->SetActive(false);
		pickUpColliders.push_back(pickupCollider);
	}

	// collider
	damageCollider->pos = pos;
	pickUpColliders[pickUpRangeIdx]->pos = pos;

	// 기본 설정
	player_id = PLAYER_ID::BAELZ;
	action_status = PLAYER_STATUS::IDLE;
	attackDir = Vector2(1.0f, 0.0f);
	isLookingRight = true;

	is_active = true;
	damageCollider->is_active = true;
	pickUpColliders[pickUpRangeIdx]->is_active = true;
}

Baelz::~Baelz()
{
	/*delete VS;
	delete PS;
	delete CB;

	for (Clip* c : clips)
		delete c;

	if (damageCollider != nullptr)
		delete damageCollider;
	if (pickUpCollider != nullptr)
		delete pickUpCollider;*/
}

void Baelz::Update()
{
	if (!is_active||isPause)return;

	switch (action_status)
	{
	case Player::PLAYER_STATUS::IDLE:
	{
		if (KEY_CON->Press(VK_LEFT) || KEY_CON->Press(VK_RIGHT)
			|| KEY_CON->Press(VK_UP) || KEY_CON->Press(VK_DOWN))
		{
			SetStatus(PLAYER_STATUS::MOVE);
		}

	}
	break;
	case Player::PLAYER_STATUS::MOVE:
	{
		// 이동 방향 지정
		CheckMoveDir();
		if (abs(moveDir.x) < 0.00001f && abs(moveDir.y) < 0.00001f)
		{
			SetStatus(PLAYER_STATUS::IDLE);
		}
		else
		{
			pos += moveDir * speed * DELTA;
		}
	}
	break;
	default:
		break;
	}

	UpdateDefault();

	clips[(UINT)action_status]->Update();
	scale = clips[(UINT)action_status]->GetFrameSize() * size /
		clips[(UINT)action_status]->GetFrameOriginSize() * Vector2(2.5f, 1.5f);

	if (!isLookingRight)
	{
		scale = scale * Vector2(-1.0f, 1.0f);
	}

	WorldUpdate();

	// collider update
	damageCollider->pos = pos + Vector2(2.0f, 8.0f);
	damageCollider->WorldUpdate();

	pickUpColliders[pickUpRangeIdx]->pos = pos;
	pickUpColliders[pickUpRangeIdx]->WorldUpdate();
}

void Baelz::Render()
{
	if (!is_active)return;

	VS->Set();
	PS->Set();

	WB->SetVS(0);
	CB->SetPS(0);

	clips[(UINT)action_status]->Render();

	damageCollider->Render();
	pickUpColliders[pickUpRangeIdx]->Render();
}

void Baelz::PostRender()
{
	if (!is_active)return;

	// Bdgin() ~ End() 아예 새 창을 열어서 써 놓음
	//ImGui::Begin("Watsib's Status", (bool*)1);
	ImGui::NewLine();
	//ImGui::BeginChild("Watson's Status");
	ImGui::Text("Baelz's HP %d/%d", (int)HP, (int)MaxHP);
	ImGui::SliderFloat("Baelz's moveSpeed", &speed, 0.0f, 1000.0f);
	ImGui::SliderFloat2("Baelz's moveDir", (float*)&moveDir, -1.0f, 1.0f);
	ImGui::SliderFloat2("Baelz's attack_dir", (float*)&attackDir, -1.0f, 1.0f);
	ImGui::Text("Now Baelz looking at %d", isLookingRight);
	ImGui::Text("EXP : %f/%f", nowExp, nowMaxExp);
	//ImGui::EndChild();
	//ImGui::End();
}

void Baelz::SetStatus(PLAYER_STATUS newStatus, UINT playOption)
{
	clips[(UINT)action_status]->Stop();
	action_status = newStatus;
	clips[(UINT)action_status]->Play(playOption);
}