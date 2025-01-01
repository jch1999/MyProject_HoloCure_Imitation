#include "framework.h"
#include "Kiara.h"

Kiara::Kiara(float MaxHP, float atk, float speed, float crt, float pickUpRange, float delay, Vector2 inIdleSize,Vector2 inMoveSize)
	:Player(MaxHP, atk, speed, crt, pickUpRange, delay, 0, inIdleSize)
	,idleSize(inIdleSize)
	,moveSize(inMoveSize)
{
	wstring file = L"Textures/Player/PC Computer - HoloCure - Save the Fans - Takanashi Kiara_rm_bg.png";
	
	// clips

	// PLAYER_STATUS::IDLE�� �����ϴ� �ִϸ��̼��� �ִ� ��Ʈ
	idleFrames.emplace_back(make_shared<const Frame>(file, 28, 61, 24, 32)); 
	idleFrames.emplace_back(make_shared<const Frame>(file, 92, 60, 24, 33));
	idleFrames.emplace_back(make_shared<const Frame>(file, 158, 61, 24, 32));
	idleFrames.emplace_back(make_shared<const Frame>(file, 223, 60, 24, 33));
	// �̸� Clip���� ����� clips�� ����
	clips.emplace_back(make_shared<Clip>(idleFrames, Clip::CLIP_TYPE::LOOP, 1.0f / 4.5f));
	//frames.clear();

	// PLAYER_STATUS::MOVE�� �����ϴ� �ִϸ��̼��� �ִ� ��Ʈ
	moveFrames.emplace_back(make_shared<const Frame>(file, 15, 137, 39, 32));
	moveFrames.emplace_back(make_shared<const Frame>(file, 79, 138, 39, 32));
	moveFrames.emplace_back(make_shared<const Frame>(file, 143, 140, 39, 32));
	moveFrames.emplace_back(make_shared<const Frame>(file, 209, 137, 39, 32));
	moveFrames.emplace_back(make_shared<const Frame>(file, 275, 138, 39, 32));
	moveFrames.emplace_back(make_shared<const Frame>(file, 340, 140, 39, 32));

	clips.emplace_back(make_shared<Clip>(moveFrames, Clip::CLIP_TYPE::LOOP, 1.0f / 6.0f));
	//frames.clear();

	// Idle collider
	kiaraCollider.emplace_back(new RectCollider(idleSize));
	colliderOffset.emplace_back(Vector2(0.0f, 5.0f));
	renderScales.emplace_back(Vector2(1.5f, 1.5f));
	// Move collider
	kiaraCollider.emplace_back(new RectCollider(moveSize));
	colliderOffset.emplace_back(Vector2(10.0f, 0.0f));
	renderScales.emplace_back(Vector2(2.5f, 1.5f));

	damageCollider = kiaraCollider[(UINT)PLAYER_STATUS::IDLE];
	for (int i = 0; i < 20; i++)
	{
		pickUpColliders.emplace_back(new CircleCollider(defaultPickUpRange * (1.0f + 0.2f * i)));
		pickUpColliders[i]->SetActive(false);
	}

	// collider
	damageCollider->pos = pos;
	pickUpColliders[pickUpRangeIdx]->pos = pos;

	// �⺻ ����
	player_id = PLAYER_ID::KIARA;
	action_status = PLAYER_STATUS::IDLE;
	attackDir = Vector2(1.0f, 0.0f);
	isLookingRight = true;

	is_active = true;
	damageCollider->is_active = true;
	pickUpColliders[pickUpRangeIdx]->is_active = true;
	clips[(UINT)action_status]->Play();
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
		// �̵� ���� ����
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

	scale = clips[(UINT)action_status]->GetFrameSize() * size /
		clips[(UINT)action_status]->GetFrameOriginSize() * renderScales[(UINT)action_status];
	clips[(UINT)action_status]->Update();

	if (!isLookingRight)
	{
		scale = scale * Vector2(-1.0f, 1.0f);
	}

	WorldUpdate();

	// collider update
	damageCollider->pos = pos + colliderOffset[(UINT)action_status]
		* ((isLookingRight) ? Vector2(1.0f, 1.0f) : Vector2(-1.0f, 1.0f));
	damageCollider->WorldUpdate();

	pickUpColliders[pickUpRangeIdx]->pos = pos;
	pickUpColliders[pickUpRangeIdx]->WorldUpdate();
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
	pickUpColliders[pickUpRangeIdx]->Render();
}

void Kiara::PostRender()
{
	if (!is_active)return;

	// Bdgin() ~ End() �ƿ� �� â�� ��� �� ����
	//ImGui::Begin("Watsib's Status", (bool*)1);
	ImGui::NewLine();
	//ImGui::BeginChild("Watson's Status");
	ImGui::Text("Kiara's HP %d/%d", (int)HP, (int)MaxHP);
	ImGui::SliderFloat("Kiara's moveSpeed", &speed, 0.0f, 1000.0f);
	ImGui::SliderFloat2("Kiara's moveDir", (float*)&moveDir, -1.0f, 1.0f);
	ImGui::SliderFloat2("Kiara's attackDir", (float*)&attackDir, -1.0f, 1.0f);
	ImGui::Text("Now Kiara looking at %d", isLookingRight);
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
		size = idleSize;
	}
	else
	{
		damageCollider->SetActive(false);
		damageCollider = kiaraCollider[(UINT)PLAYER_STATUS::MOVE];
		damageCollider->SetActive(true);
		size = moveSize;
	}
}