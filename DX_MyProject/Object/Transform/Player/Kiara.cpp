#include "framework.h"
#include "Kiara.h"

Kiara::Kiara(float MaxHP, float atk, float speed, float crt, float pickUpRange, float delay, Vector2 idle_size,Vector2 move_size)
	:Player(MaxHP, atk, speed, crt, pickUpRange, delay, 0, idle_size)
	,idle_size(idle_size)
	,move_size(move_size)
{
	wstring file = L"Textures/Player/PC Computer - HoloCure - Save the Fans - Takanashi Kiara_rm_bg.png";
	Texture* t = Texture::Add(file);

	// clips
	vector<Frame*> frames;

	// PLAYER_STATUS::IDLE에 대응하는 애니메이션을 넣는 파트
	frames.push_back(new Frame(file, 28, 61, 24, 32));
	frames.push_back(new Frame(file, 92, 60, 24, 33));
	frames.push_back(new Frame(file, 158, 61, 24, 32));
	frames.push_back(new Frame(file, 223, 60, 24, 33));
	// 이를 Clip으로 만들어 clips에 저장
	AddClip(new Clip(frames, Clip::CLIP_TYPE::LOOP, 1.0f / 4.5f));
	frames.clear();

	// PLAYER_STATUS::MOVE에 대응하는 애니메이션을 넣는 파트
	frames.push_back(new Frame(file, 15, 137, 39, 32));
	frames.push_back(new Frame(file, 79, 138, 39, 32));
	frames.push_back(new Frame(file, 143, 140, 39, 32));
	frames.push_back(new Frame(file, 209, 137, 39, 32));
	frames.push_back(new Frame(file, 275, 138, 39, 32));
	frames.push_back(new Frame(file, 340, 140, 39, 32));

	AddClip(new Clip(frames, Clip::CLIP_TYPE::LOOP, 1.0f / 6.0f));
	frames.clear();

	// Idle collider
	kiaraCollider.push_back(new RectCollider(idle_size));
	colliderOffset.push_back(Vector2(0.0f, 5.0f));
	renderScales.push_back(Vector2(1.5f, 1.5f));
	// Move collider
	kiaraCollider.push_back(new RectCollider(move_size));
	colliderOffset.push_back(Vector2(10.0f, 0.0f));
	renderScales.push_back(Vector2(2.5f, 1.5f));

	damageCollider = kiaraCollider[(UINT)PLAYER_STATUS::IDLE];
	for (int i = 0; i < 20; i++)
	{
		CircleCollider* pickupCollider = new CircleCollider(default_pickUpRange * (1.0f + 0.2f * i));
		pickupCollider->SetActive(false);
		pickUpColliders.push_back(pickupCollider);
	}

	// collider
	damageCollider->pos = pos;
	pickUpColliders[idx_pickUpRange]->pos = pos;

	// 기본 설정
	player_id = PLAYER_ID::KIARA;
	action_status = PLAYER_STATUS::IDLE;
	attack_dir = Vector2(1.0f, 0.0f);
	is_looking_right = true;

	is_active = true;
	damageCollider->is_active = true;
	pickUpColliders[idx_pickUpRange]->is_active = true;
}

Kiara::~Kiara()
{
}

void Kiara::Update()
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
		if (abs(move_dir.x) < 0.00001f && abs(move_dir.y) < 0.00001f)
		{
			SetStatus(PLAYER_STATUS::IDLE);
		}
		else
		{
			pos += move_dir * speed * DELTA;
		}
	}
	break;
	default:
		break;
	}
	
	UpdateDefault();

	clips[(UINT)action_status]->Update();
	scale = clips[(UINT)action_status]->GetFrameSize() * size /
		clips[(UINT)action_status]->GetFrameOriginSize()*renderScales[(UINT)action_status];

	if (!is_looking_right)
	{
		scale = scale * Vector2(-1.0f, 1.0f);
	}

	WorldUpdate();

	// collider update
	damageCollider->pos = pos + colliderOffset[(UINT)action_status]
		* ((is_looking_right) ? Vector2(1.0f, 1.0f) : Vector2(-1.0f, 1.0f));
	damageCollider->WorldUpdate();

	pickUpColliders[idx_pickUpRange]->pos = pos;
	pickUpColliders[idx_pickUpRange]->WorldUpdate();
}

void Kiara::Render()
{
	if (!is_active)return;

	VS->Set();
	PS->Set();

	WB->SetVS(0);
	CB->SetPS(0);

	clips[(UINT)action_status]->Render();

	damageCollider->Render();
	pickUpColliders[idx_pickUpRange]->Render();
}

void Kiara::PostRender()
{
	if (!is_active)return;

	// Bdgin() ~ End() 아예 새 창을 열어서 써 놓음
	//ImGui::Begin("Watsib's Status", (bool*)1);
	ImGui::NewLine();
	//ImGui::BeginChild("Watson's Status");
	ImGui::Text("Kiara's HP %d/%d", (int)HP, (int)MaxHP);
	ImGui::SliderFloat("Kiara's moveSpeed", &speed, 0.0f, 1000.0f);
	ImGui::SliderFloat2("Kiara's move_dir", (float*)&move_dir, -1.0f, 1.0f);
	ImGui::SliderFloat2("Kiara's attack_dir", (float*)&attack_dir, -1.0f, 1.0f);
	ImGui::Text("Now Kiara looking at %d", is_looking_right);
	ImGui::Text("EXP : %f/%f", nowExp, nowMaxExp);
	//ImGui::EndChild();
	//ImGui::End();
}

void Kiara::SetStatus(PLAYER_STATUS newStatus, UINT playOption)
{
	clips[(UINT)action_status]->Stop();
	action_status = newStatus;
	clips[(UINT)action_status]->Play(playOption);

	if (action_status == PLAYER_STATUS::IDLE)
	{
		damageCollider->SetActive(false);
		damageCollider = kiaraCollider[(UINT)PLAYER_STATUS::IDLE];
		damageCollider->SetActive(true);
		size = idle_size;
	}
	else
	{
		damageCollider->SetActive(false);
		damageCollider = kiaraCollider[(UINT)PLAYER_STATUS::MOVE];
		damageCollider->SetActive(true);
		size = move_size;
	}
}