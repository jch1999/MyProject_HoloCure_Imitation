#include "framework.h"

vector<shared_ptr<const Frame>>& PlayerIcon::GetPlayerIconFrames()
{
	static vector<shared_ptr<const Frame>> playerIconFrames;
	return playerIconFrames;
}

int& PlayerIcon::GetPlayerIconUseCnt()
{
	static int playerIconUseCnt = 0;
	return playerIconUseCnt;
}

PlayerIcon::PlayerIcon(Vector2 inSize, Vector2 inScale, Vector2 inOffset)
	:UI(inSize, inScale, inOffset)
{
	if (GetPlayerIconFrames().empty())
	{
		InitFrame();
	}

	id = UI::UI_ID::PLAYER_ICON;
	type = UI::UI_TYPE::ICON;
	state = UI::UI_STATE::IDLE;
	additionalScale = Vector2(1, 1);
	is_active = false;

	++GetPlayerIconUseCnt();
}

PlayerIcon::~PlayerIcon()
{
	if ((--GetPlayerIconUseCnt()) == 0)
	{
		ClearFrame();
	}
}

void PlayerIcon::Update()
{
	if (!is_active)return;

	auto& currentFrame = GetPlayerIconFrames()[clipIdx];
	scale = currentFrame->GetFrameSize() * uiSize / currentFrame->GetFrameOriginSize() * uiScale * additionalScale;

	pos = target->pos + offset;
	WorldUpdate();
}

void PlayerIcon::Render()
{
	if (!is_active)return;
	VS->Set();
	PS->Set();

	WB->SetVS(0);
	CB->SetPS(0);

	GetPlayerIconFrames()[clipIdx]->Render();
}

void PlayerIcon::SetID(UI::UI_ID id)
{
	this->id = id;
	switch (id)
	{
	case UI::UI_ID::PLAYER_ICON:
	{
		// PlayerIconFrame의 경우 생성시기가 UIManager에 Player가 대입되는 시기보다 빠름
		// 따라서 다른 곳에서 player정보를 가져와야 함
		Player::PLAYER_ID pId = EnemySpawner::Get()->GetPlayer()->player_id;
		switch (pId)
		{
		case Player::PLAYER_ID::WATSON:
		{
			clipIdx = 0;
		}
		break;
		case Player::PLAYER_ID::KIARA:
		{
			clipIdx = 1;
		}
		break;
		case Player::PLAYER_ID::BAELZ:
		{
			clipIdx = 2;
		}
		break;
		default:
			break;
		}
		CB->data.colour = Float4(1.0f, 1.0f, 1.0f, 1.0f);
		SetSize(Vector2(43.0f, 38.0f));
	}
		break;
	case UI::UI_ID::PLAYER_FULL_ICON:
	{
		// PlayerIconFrame의 경우 생성시기가 UIManager에 Player가 대입되는 시기보다 빠름
		// 따라서 다른 곳에서 player정보를 가져와야 함
		Player::PLAYER_ID pId = EnemySpawner::Get()->GetPlayer()->player_id;
		switch (pId)
		{
		case Player::PLAYER_ID::WATSON:
		{
			clipIdx = 3;
			SetSize(Vector2(73.0f, 105.0f));
		}
		break;
		case Player::PLAYER_ID::KIARA:
		{
			clipIdx = 4;
			SetSize(Vector2(63.0f, 115.0f));
		}
		break;
		case Player::PLAYER_ID::BAELZ:
		{
			clipIdx = 5;
			SetSize(Vector2(73.0f, 112.0f));
		}
		break;
		default:
			break;
		}
		CB->data.colour = Float4(0.95f, 0.95f, 0.95f, 0.85f);
	}
		break;
	default:
		break;
	}
}

void PlayerIcon::InitFrame()
{
	auto& playerIconFrames = GetPlayerIconFrames();
	if (!(playerIconFrames.empty())) return;

	vector<wstring> files =
	{
		// PlayerIcon & Defulat Weapon Skill Icon
		L"Textures/Player/PC Computer - HoloCure - Save the Fans - Amelia Watson_rm_bg.png",
		L"Textures/Player/PC Computer - HoloCure - Save the Fans - Takanashi Kiara_rm_bg.png",
		L"Textures/Player/PC Computer - HoloCure - Save the Fans - Hakos Baelz_rm_bg.png",
	};

	// Player Icon
	// Watson
	playerIconFrames.emplace_back(make_shared<const Frame>(files[0], 10, 2363, 43, 38));
	// Kiara
	playerIconFrames.emplace_back(make_shared<const Frame>(files[1], 10, 3953, 43, 38));
	// Baelz
	playerIconFrames.emplace_back(make_shared<const Frame>(files[2], 10, 802, 43, 38));

	// Player Full Icon
	// Watson
	playerIconFrames.emplace_back(make_shared<const Frame>(files[0], 7, 2419, 73, 105));
	// Kiara
	playerIconFrames.emplace_back(make_shared<const Frame>(files[1], 7, 4008, 63, 115));
	// Baelz
	playerIconFrames.emplace_back(make_shared<const Frame>(files[2], 7, 858, 73, 112));
}

void PlayerIcon::ClearFrame()
{
	GetPlayerIconFrames().clear();
}
