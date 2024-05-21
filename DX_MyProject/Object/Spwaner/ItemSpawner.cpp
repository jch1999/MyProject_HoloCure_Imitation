#include "framework.h"

ItemSpawner::ItemSpawner()
	:anvilDefualt(1.0f / 1301.0f),anvilDropRate(anvilDefualt),anvilUseCnt(1)
	,magnetDropRate(1.0f / 3000.0f)
	,coinDefault(1.0f / 90.0f),coinRate(coinDefault),coinValue(10),nowCoinValue(10)
{
	for (int i = 0; i < 100; i++)
	{
		item_list.push_back(new Exp());
		item_list.push_back(new Coin());
	}
	for (int i = 0; i < 10; i++)
	{
		item_list.push_back(new Anvil());
	}
}

ItemSpawner::~ItemSpawner()
{
	for (auto i : item_list)
		delete i;
}

void ItemSpawner::GenerateItem(Vector2 pos, int value)
{
	float rand = Random::Get()->GetRandomFloat(0.0f, 1.0f);

	if (rand <= anvilDropRate)
	{
		//GenerateItem(pos, Item::ITEM_ID::ANVIL, anvilUseCnt);
	}
	else if (rand <= anvilDropRate + magnetDropRate)
	{
		GenerateItem(pos, Item::ITEM_ID::EXP_MAGNET, 0);
	}
	else if (rand <= anvilDropRate + magnetDropRate + coinRate)
	{
		GenerateItem(pos, Item::ITEM_ID::COIN, coinValue);
	}
	else
	{
		GenerateItem(pos, Item::ITEM_ID::EXP, value);
	}
}

void ItemSpawner::GenerateItem(Vector2 pos, Item::ITEM_ID id, int value)
{
	switch (id)
	{
	case Item::ITEM_ID::EXP:
	{
		Item* target = nullptr;
		for (auto i : item_list)
		{
			if (i->is_active)continue;
			if (i->type == Item::ITEM_TYPE::EXP)
			{
				target = i;
				break;
			}
		}

		if (target == nullptr)
		{
			Item* exp = new Exp();
			target = exp;
			target->SetPlayer(player);
			item_list.push_back(exp);
		}
		target->SetStatus(Item::ITEM_ID::EXP, value);
		target->SetPos(pos);
		target->SetState(Item::ITEM_STATE::IDLE);
		target->Respawn();
	}
		break;
	case Item::ITEM_ID::EXP_MAGNET:
	{
		Item* target = nullptr;
		for (auto i : item_list)
		{
			if (!i->is_active)continue;
			if (i->type == Item::ITEM_TYPE::EXP)
			{
				target = i;
				break;
			}
		}

		if (target == nullptr)
		{
			Item* exp = new Exp();
			target = exp;
			target->SetPlayer(player);
			item_list.push_back(exp);
		}
		target->SetStatus(Item::ITEM_ID::EXP_MAGNET);
		target->SetPos(pos);
		target->SetState(Item::ITEM_STATE::IDLE);
		target->Respawn();
	}
		break;
	case Item::ITEM_ID::ANVIL:
	{
		Item* target = nullptr;
		for (auto i : item_list)
		{
			if (!i->is_active)continue;
			if (i->type == Item::ITEM_TYPE::ANVIL)
			{
				target = i;
				break;
			}
		}

		if (target == nullptr)
		{
			Item* anvil = new Anvil();
			target = anvil;
			item_list.push_back(anvil);
		}
		target->SetStatus(Item::ITEM_ID::ANVIL);
		target->SetPos(pos);
		target->SetState(Item::ITEM_STATE::IDLE);
		target->Respawn();
	}
		break;
	case Item::ITEM_ID::GOLDEN_ANVIL:
		break;
	case Item::ITEM_ID::COIN:
	{
		Item* target = nullptr;
		for (auto i : item_list)
		{
			if (i->is_active)continue;
			if (i->type == Item::ITEM_TYPE::COIN)
			{
				target = i;
				break;
			}
		}

		if (target == nullptr)
		{
			Item* coin = new Coin();
			target = coin;
			item_list.push_back(coin);
		}
		target->SetPlayer(player);
		target->SetStatus(Item::ITEM_ID::COIN, value);
		target->SetPos(pos);
		target->SetState(Item::ITEM_STATE::IDLE);
		target->Respawn();
	}
		break;
	case Item::ITEM_ID::REWORD_BOX:
		break;
	default:
		break;
	}
}

void ItemSpawner::Update()
{
	if (player->isPause)return;
	for (auto i : item_list)
	{
		if (!i->is_active)continue;
		
		/*
		for (auto i2 : item_list) // O(n^2) 개선 필요..
		{
			if (!i2->is_active)continue;

			if (i != i2)
			{
				if (i->id == Item::ITEM_ID::EXP && i2->id == Item::ITEM_ID::EXP)
				{
					if (i->GetCollider()->isCollision(i2->GetCollider()))
					{
						i->pos = (i->pos + i2->pos) / 2.0f;
						i->SetStatus(Item::ITEM_ID::EXP, ((Exp*)i)->GetAmount() + ((Exp*)i2)->GetAmount());
						i->GetCollider()->pos = i->pos;
						i2->is_active = false;
						i->Respawn();
					}
				}
				else if (i->id == Item::ITEM_ID::COIN && i2->id == Item::ITEM_ID::COIN)
				{
					if (i->GetCollider()->isCollision(i2->GetCollider()))
					{
						i->pos = (i->pos + i2->pos) / 2.0f;
						i->SetStatus(Item::ITEM_ID::COIN, ((Coin*)i)->GetAmount() + ((Coin*)i2)->GetAmount());
						i2->is_active = false;
						i->Respawn();
					}
				}
			}
		}
		*/
		i->Update();
		
		// 아이템 획득
		if (i->GetCollider()->isCollision(player->GetDamageCollider()))
		{
			i->SetState(Item::ITEM_STATE::USED);
		}
		// 추적형 아이템 활성화
		else if (i->GetCollider()->isCollision(player->GetPickUpcollider()))
		{
			i->SetState(Item::ITEM_STATE::ACTIVE);
		}
	}
}

void ItemSpawner::Render()
{
	for (auto i : item_list)
		i->Render();
}

void ItemSpawner::PostRneder()
{
	/*
	for (auto i : item_list)
		i->PostRender();
	*/
	ImGui::Text("Now Coin : %d", nowCoinValue);
}

void ItemSpawner::SetPlayer(Player* p)
{
	player = p;
	for (auto i : item_list)
	{
		if (i->type == Item::ITEM_TYPE::EXP)
			i->SetPlayer(player);
	}
}
