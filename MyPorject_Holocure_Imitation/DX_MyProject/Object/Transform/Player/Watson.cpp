#include "framework.h"
#include "Watson.h"

Watson::Watson(float MaxHP,float atk, float speed,float crt,float pickUpRange,float delay,Vector2 size)
	:Player(MaxHP,atk,speed,crt,pickUpRange,delay,0,size)
{
	wstring file = L"Textures/Player/PC Computer - HoloCure - Save the Fans - Amelia Watson_rm_bg.png";
	Texture* t = Texture::Add(file);

	// clips
	vector<Frame*> frames;

	// PLAYER_STATUS::IDLE에 대응하는 애니메이션을 넣는 파트
	// 스프라이트 크기
	Vector2 this_frame_size = { 25.f,30.f };
	// 스프라이트의 왼쪽 위 좌표
	Vector2 init_pos = { 25,63 };

	for (int i = 0; i < 3; i++)
	{
		frames.push_back(new Frame(file, init_pos.x + 65 * i, init_pos.y,
			this_frame_size.x, this_frame_size.y));
	}

	// 이를 Clip으로 만들어 clips에 저장
	AddClip(new Clip(frames, Clip::CLIP_TYPE::LOOP, 1.0f / 4.5f));
	frames.clear();

	// PLAYER_STATUS::MOVE에 대응하는 애니메이션을 넣는 파트
	init_pos = Vector2(28, 141);
	this_frame_size = Vector2(24, 30);
	for (int i = 0; i < 6; i++)
	{
		frames.push_back(new Frame(file, init_pos.x + 65 * i, init_pos.y,
			this_frame_size.x, this_frame_size.y));
	}
	AddClip(new Clip(frames, Clip::CLIP_TYPE::LOOP, 1.0f / 6.0f));
	frames.clear();

	damageCollider = new RectCollider(size);
	for (int i = 0; i < 6; i++)
	{
		CircleCollider* pickupCollider = new CircleCollider(default_pickUpRange * (1.0f + 0.2f * i));
		pickupCollider->SetActive(false);
		pickUpColliders.push_back(pickupCollider);
	}

	// collider
	damageCollider->pos = pos;
	pickUpColliders[idx_pickUpRange]->pos = pos;

	// 기본 설정
	player_id = PLAYER_ID::WATSON;
	action_status = PLAYER_STATUS::IDLE;
	attack_dir = Vector2(1.0f, 0.0f);
	is_looking_right = true;

	is_active = true;
	damageCollider->is_active = true;
	pickUpColliders[idx_pickUpRange]->is_active = true;
}

Watson::~Watson()
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

void Watson::Update()
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

	clips[(UINT)action_status]->Update();
	scale = clips[(UINT)action_status]->GetFrameSize() * size /
		clips[(UINT)action_status]->GetFrameOriginSize() * Vector2(2.0f, 1.5f);

	if (!is_looking_right)
	{
		scale = scale * Vector2(-1.0f, 1.0f);
	}

	WorldUpdate();
	
	// collider update
	damageCollider->pos = pos + Vector2(3.0f, 3.0f);
	damageCollider->WorldUpdate();

	pickUpColliders[idx_pickUpRange]->pos = pos;
	pickUpColliders[idx_pickUpRange]->WorldUpdate();
}

void Watson::Render()
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

void Watson::PostRender()
{
	if (!is_active)return;

	// Bdgin() ~ End() 아예 새 창을 열어서 써 놓음
	//ImGui::Begin("Watsib's Status", (bool*)1);
	ImGui::NewLine();
	//ImGui::BeginChild("Watson's Status");
	ImGui::Text("Watson's HP %d/%d", (int)HP, (int)MaxHP);
	ImGui::SliderFloat("Watson's moveSpeed", &speed,0.0f,1000.0f);
	ImGui::SliderFloat2("Watson's move_dir", (float*)&move_dir, -1.0f, 1.0f);
	ImGui::SliderFloat2("Watson's attack_dir", (float*)&attack_dir, -1.0f, 1.0f);
	ImGui::Text("Now Watson looking at %d", is_looking_right);
	ImGui::Text("EXP : %f/%f", nowExp, expLimits[level]);
	//ImGui::EndChild();
	//ImGui::End();
}

void Watson::SetStatus(PLAYER_STATUS newStatus,UINT playOption)
{
	clips[(UINT)action_status]->Stop();
	action_status = newStatus;
	clips[(UINT)action_status]->Play(playOption);
}