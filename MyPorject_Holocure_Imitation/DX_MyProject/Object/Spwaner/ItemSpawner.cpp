#include "framework.h"

ItemSpawner::ItemSpawner()
	:anvilDefualt(1.0f / 1301.0f),anvilDropRate(anvilDefualt),anvilUseCnt(1)
	,magnetDropRate(1.0f / 3000.0f)
	,coinDefault(1.0f / 90.0f),coinRate(coinDefault),coinValue(10),nowCoinValue(0)
	,foodDefault(1.0f/200.0f),foodRate(foodDefault)
	,nowTime(FIXED_INTERVAL)
{
	for (int i = 0; i < 100; i++)
	{
		item_list.push_back(new Exp());
		item_list.push_back(new Coin());
	}
	for (int i = 0; i < 10; i++)
	{
		item_list.push_back(new Anvil());
		item_list.push_back(new Hambureger());
	}
	item_list.push_back(new RewardBox());
	item_list.push_back(new RewardBox());
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
		GenerateItem(pos, Item::ITEM_ID::ANVIL, anvilUseCnt);
	}
	else if (rand <= anvilDropRate + magnetDropRate)
	{
		GenerateItem(pos, Item::ITEM_ID::EXP_MAGNET, 0);
	}
	else if (rand <= anvilDropRate + magnetDropRate + coinRate)
	{
		GenerateItem(pos, Item::ITEM_ID::COIN, coinValue);
	}
	else if (rand <= anvilDropRate + magnetDropRate + coinRate + foodRate)
	{
		GenerateItem(pos, Item::ITEM_ID::HAMBURGER, player->GetMaxHP() * 0.2f);
	}
	else
	{
		GenerateItem(pos, Item::ITEM_ID::EXP, value);
		//GenerateItem(pos, Item::ITEM_ID::REWORD_BOX, anvilUseCnt);
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
		target->Respawn();
	}
		break;
	case Item::ITEM_ID::ANVIL:
	{
		Item* target = nullptr;
		for (auto i : item_list)
		{
			if (i->is_active)continue;
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
		target->SetStatus(Item::ITEM_ID::ANVIL,value);
		target->SetPos(pos);
		target->Respawn();
	}
		break;
	case Item::ITEM_ID::GOLDEN_ANVIL:
	{
		Item* target = nullptr;
		for (auto i : item_list)
		{
			if (i->is_active)continue;
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
		target->SetStatus(Item::ITEM_ID::GOLDEN_ANVIL);
		target->SetPos(pos);
		target->Respawn();
	}
		break;
	case Item::ITEM_ID::COIN:
	{
		Item* target = nullptr;
		for (auto i : item_list)
		{
			if (i->is_active)continue;
			if (i->type == Item::ITEM_TYPE::ANVIL)
			{
				target = i;
				break;
			}
		}

		if (target == nullptr)
		{
			Item* coin = new Anvil();
			target = coin;
			item_list.push_back(coin);
		}
		target->SetPlayer(player);
		target->SetStatus(Item::ITEM_ID::GOLDEN_ANVIL, value);
		target->SetPos(pos);
		target->Respawn();
	}
		break;
	case Item::ITEM_ID::REWORD_BOX:
	{
		Item* target = nullptr;
		for (auto i : item_list)
		{
			if (i->is_active)continue;
			if (i->type == Item::ITEM_TYPE::REWARD_BOX)
			{
				target = i;
				break;
			}
		}

		if (target == nullptr)
		{
			Item* box = new RewardBox();
			target = box;
			item_list.push_back(box);
		}
		target->SetStatus(Item::ITEM_ID::REWORD_BOX);
		target->SetPos(pos);
		target->SetState(Item::ITEM_STATE::IDLE);
		target->Respawn();
	}
		break;
	case Item::ITEM_ID::HAMBURGER:
	{
		Item* target = nullptr;
		for (auto i : item_list)
		{
			if (i->is_active)continue;
			if (i->type == Item::ITEM_TYPE::FOOD)
			{
				target = i;
				break;
			}
		}

		if (target == nullptr)
		{
			Item* food = new Hambureger();
			target = food;
			item_list.push_back(food);
		}
		target->SetPlayer(player);
		target->SetStatus(Item::ITEM_ID::HAMBURGER, value);
		target->SetPos(pos);
		target->SetState(Item::ITEM_STATE::IDLE);
		target->Respawn();
	}
		break;
	default:
		break;
	}
}

void ItemSpawner::Update()
{
	nowTime -= DELTA;
	if (isPause)return;
	
	for (auto i : item_list)
	{
		if (!i->is_active)continue;
		if (!(i->state == Item::ITEM_STATE::IDLE))continue;
		switch (i->id)
		{
		case Item::ITEM_ID::EXP:
		case Item::ITEM_ID::COIN:
		{
			pair<int, int> iPos = make_pair(i->pos.x / CELL_X, i->pos.y / CELL_Y);
			list<Item*> itemList = GetPartition(iPos);
			i->SetAddtionalDir(Vector2(0, 0));
			for (auto i2 : itemList)
			{
				if (!i2->is_active)continue;
				if (!(i2->state == Item::ITEM_STATE::IDLE))continue;
				if (i == i2)continue;

				if (i->GetCollider()->isCollision(i2->GetCollider()))
				{
					if (i->id == i2->id) // 같은 종류면 서로 당기기
					{
						if ((i->pos - i2->pos).GetLength() < 0.1f)// 거리가 0.1f이하이면 합치기
						{
							i->SetAmount(i->GetAmount() + i2->GetAmount());
							i2->SetActive(false);
						}
						else
						{
							i->SetAddtionalDir(i->GetAddtionalDir() + (i2->pos - i->pos).Normalized());
						}
					}
					//else // 다른 종류면 서로 밀어내기
					//{
					//	i->SetAddtionalDir(i->GetAddtionalDir() + (i->pos - i2->pos).Normalized());
					//}
				}
			}
		}
		default:
			break;
		}
	}

	for (auto i : item_list)
	{
		if (!i->is_active)continue;
		i->Update();
	}

	pair<int, int> pPos = make_pair(player->pos.x / CELL_X, player->pos.y / CELL_Y);
	list<Item*> itemList = GetPartition(pPos);
	for (auto i : itemList)
	{
		switch (i->type)
		{
		case Item::ITEM_TYPE::EXP:
		case Item::ITEM_TYPE::COIN:
		case Item::ITEM_TYPE::FOOD:
		{
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
			break;
		case Item::ITEM_TYPE::ANVIL:
		case Item::ITEM_TYPE::REWARD_BOX:
		{
			if (i->GetCollider()->isCollision(player->GetDamageCollider()))
			{
				i->SetState(Item::ITEM_STATE::ACTIVE);
			}
		}
			break;
		default:
			break;
		}
		
	}

	if (nowTime < 0.0f)
	{
		nowTime += FIXED_INTERVAL;
		FixedUpdate();
	}
}

void ItemSpawner::FixedUpdate()
{
	// 기존 정보 제거
	partition.clear();

	// 모든 Item를 각 칸에 맞게 
	for (auto e : item_list)
	{
		if (!e->is_active)continue;
		int cell_x = (int)(e->pos.x) / CELL_X;
		int cell_y = (int)(e->pos.y) / CELL_Y;
		pair<int, int> iPos = make_pair(cell_x, cell_y);
		for (int i = -1; i <= 1; i++)
		{
			for (int j = -1; j <= 1; j++)
			{
				pair<int, int> pos = make_pair(iPos.first + i, iPos.second + j);
				partition[pos].push_back(e);
			}
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
