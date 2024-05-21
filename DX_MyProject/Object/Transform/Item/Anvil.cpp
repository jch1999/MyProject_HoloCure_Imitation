#include "framework.h"

Anvil::Anvil(Vector2 pos, Vector2 size)
	:Item()
{
	id = ITEM_ID::ANVIL;
	type = ITEM_TYPE::ANVIL;
}

Anvil::~Anvil()
{
}

void Anvil::Update()
{
	if (!is_active)return;
}

void Anvil::Render()
{
	if (!is_active)return;
}

void Anvil::PostRender()
{
	if (!is_active)return;
}

void Anvil::Respawn()
{
}

void Anvil::SetStatus(Item::ITEM_ID id, int value)
{
	switch (id)
	{
	case Item::ITEM_ID::ANVIL:
	{
		SetUseCnt(value);
	}
		break;
	case Item::ITEM_ID::GOLDEN_ANVIL:
	{
		useCnt = 1;
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
}
