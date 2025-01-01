#include "framework.h"



vector<shared_ptr<const Frame>>& Anvil::GetAnvilFrames()
{
	static vector<shared_ptr<const Frame>> anvilFrames;
	return anvilFrames;
}

int& Anvil::GetAnvilSpawnCnt()
{
	static int anvilSpawnCnt = 0;
	return anvilSpawnCnt;
}

Anvil::Anvil(Vector2 pos, Vector2 size)
	:Item()
	,coolTime(0.0f)
	,usableCnt(0),nowUsedCnt(0)
{
	if (GetAnvilFrames().empty())
	{
		InitFrame();
	}

	collider = new RectCollider(Vector2(41.0f, 24.0f) * 1.5f);
	id = ITEM_ID::ANVIL;
	type = ITEM_TYPE::ANVIL;

	light = make_shared<ItemLight>(pos);
	light->SetOffset(Vector2(0.0f, -45.0f));
	CB->data.colour = Float4(1.0f, 1.0f, 1.0f, 0.95f);

	light->SetActive(false);
	is_active = false;
	collider->SetActive(false);
}

Anvil::~Anvil()
{
	delete collider;
	light.reset();
}

void Anvil::SetUsableCnt(int inUseCnt)
{
	this->usableCnt = inUseCnt;
}

void Anvil::Update()
{
	if (!is_active)return;

	switch (state)
	{
	case Item::ITEM_STATE::IDLE:
		if (coolTime > nowTime)
		{
			collider->SetActive(false);
			nowTime += DELTA;
		}
		else
		{
			collider->SetActive(true);
		}
		break;
	case Item::ITEM_STATE::ACTIVE:
	{
		if (UIManager::Get()->GetEnhancePanel()->GetAnvil() != this)
		{
			SetState(Item::ITEM_STATE::IDLE);
		}
	}
		break;
	case Item::ITEM_STATE::USED:
	{
		
	}
		break;
	default:
		break;
	}

	light->Update(); 
	
	auto& currentFrame = GetAnvilFrames()[clipIdx];
	scale = currentFrame->GetFrameSize() * collider->Size() /
		currentFrame->GetFrameOriginSize();
	
	WorldUpdate();

	collider->pos = pos;
	collider->WorldUpdate();
}

void Anvil::Render()
{
	if (!is_active)return;
	
	VS->Set();
	PS->Set();

	WB->SetVS(0);
	CB->SetPS(0);

	GetAnvilFrames()[clipIdx]->Render();
	light->Render();
	collider->Render();
}

void Anvil::PostRender()
{
	if (!is_active)return;
	ImGui::Text("Now UsableCnt : %d", usableCnt);
	ImGui::Text("Now UsedCnt : %d", nowUsedCnt);
}

void Anvil::Respawn()
{
	state = ITEM_STATE::IDLE;

	WorldUpdate();
	collider->pos = pos;
	collider->WorldUpdate();
	light->SetPos(pos);
	light->WorldUpdate();

	auto& currentFrame = GetAnvilFrames()[clipIdx];
	scale = currentFrame->GetFrameSize() * collider->Size() /
		currentFrame->GetFrameOriginSize();
	nowTime = coolTime;
	nowUsedCnt = 0;

	is_active = true;
	collider->SetActive(true);
	light->SetActive(true);
}

void Anvil::SetStatus(Item::ITEM_ID id, int value)
{
	this->id = id;
	switch (id)
	{
	case Item::ITEM_ID::ANVIL:
	{
		SetUsableCnt(value);
		clipIdx = 0;
	}
		break;
	case Item::ITEM_ID::GOLDEN_ANVIL:
	{
		usableCnt = 1;
		clipIdx = 1;
	}
		break;
	default:
		break;
	}
}

void Anvil::SetState(ITEM_STATE state)
{
	this->state = state;
	switch (state)
	{
	case Item::ITEM_STATE::IDLE:
	{
		nowTime = 0.0f;
	}
		break;
	case Item::ITEM_STATE::ACTIVE:
	{
		UIManager::Get()->ActivateEnhancePanel();
		UIManager::Get()->GetEnhancePanel()->SetAnvil(this);
		collider->SetActive(false);
	}
		break;
	case Item::ITEM_STATE::USED:
	{
		if ((++nowUsedCnt) == usableCnt)
		{
			is_active = false;
			collider->SetActive(false);
		}
		else
		{
			SetState(ITEM_STATE::IDLE);
		}
	}
		break;
	default:
		break;
	}
}

void Anvil::SetPos(Vector2 pos)
{
	this->pos = pos; 
	collider->pos = pos;
	light->SetPos(pos);
}

void Anvil::SetAmount(int value)
{
	usableCnt = value;
}

int Anvil::GetAmount()
{
	return usableCnt;
}

void Anvil::InitFrame()
{
	auto& anvilFrames = GetAnvilFrames();
	if (!anvilFrames.empty()) return;

	wstring file = L"Textures/Item/PC Computer - HoloCure - Save the Fans - Pickups_rm_bg.png";
	
	// anvil frame
	anvilFrames.push_back(make_shared<const Frame>(file, 81.0f, 179.0f, 41.0f, 24.0f));
	// golden anvil frame
	anvilFrames.push_back(make_shared<const Frame>(file, 147.0f, 179.0f, 41.0f, 24.0f));
}

void Anvil::ClearFrame()
{
	GetAnvilFrames().clear();
}

