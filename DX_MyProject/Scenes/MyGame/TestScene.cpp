#include "framework.h"

TestScene::TestScene()
{
	player = new Baelz();
	player->pos = WIN_CENTER;

	CAM->SetTarget(player);

	//skill = new PlayDice();
	//skill->SetPlayer(player);
	/*{
		proj = new BaelzDice(Vector2(36.0f, 36.0f));
		proj->pos = player->pos + Vector2(50.0f, 100.0f);
		proj->SetStatus(100, 16, 100, 5.0f);
		proj->respwan();
		proj->move_dir = player->GetMoveDir();
	}*/
	/* {
		item = new RewardBox();
		item->pos = player->pos + Vector2(50.0f, 100.0f);
		item->SetPlayer(player);
		item->SetStatus(Item::ITEM_ID::REWORD_BOX, 0);
		item->SetState(Item::ITEM_STATE::IDLE);
		item->Respawn();
		ItemSpawner::Get()->AddItem(item);
	}*/
	ItemSpawner::Get()->SetPlayer(player);
	EnemySpawner::Get()->SetPlayer(player);
	SkillManager::Get()->SetPlayer(player);
	UIManager::Get()->SetPlayer(player);
	player->GetExp(0);
	player->CheckMoveDir();
	/*{
		enemy = new MiniBoss();
		enemy->SetEnemyName(Enemy::ENEMY_NAME::MEGA_SHRIMP);
		enemy->pos = player->pos + WIN_CENTER;
		enemy->SetPlayer(player);
		enemy->Respawn();
		EnemySpawner::Get()->AddEnemy(enemy);
	}*/
	//hpBar = new HPBar();
	//hpBar->SetTarget(player);
	//hpBar->SetOffset(Vector2(0.0f, -35.0f));
	//UIManager::Get()->AddUI(hpBar);
	//UIManager::Get()->AddUI(hpBar);
}

TestScene::~TestScene()
{
	delete player;
	//delete skill;
	//delete proj;
	//delete enemy;
	//delete item;
	EnemySpawner::Delete();
	SkillManager::Delete();
	UIManager::Delete();
}

void TestScene::Update()
{
	if (KEY_CON->Down('A'))
	{
		switch (player->player_id)
		{
		case Player::PLAYER_ID::BAELZ:
			SkillManager::Get()->GetSkillByID(Skill::SKILL_ID::PLAY_DICE)->LevelUp();
			break;
		case Player::PLAYER_ID::KIARA:
			SkillManager::Get()->GetSkillByID(Skill::SKILL_ID::PHOENIX_SWORD)->LevelUp();
			break;
		case Player::PLAYER_ID::WATSON:
			SkillManager::Get()->GetSkillByID(Skill::SKILL_ID::PISTOL_SHOT)->LevelUp();
			break;
		}
	}
	if (KEY_CON->Down('D'))
	{
		switch (player->player_id)
		{
		case Player::PLAYER_ID::BAELZ:
			SkillManager::Get()->GetSkillByID(Skill::SKILL_ID::PLAY_DICE)->LevelDown();
			break;
		case Player::PLAYER_ID::KIARA:
			SkillManager::Get()->GetSkillByID(Skill::SKILL_ID::PHOENIX_SWORD)->LevelDown();
			break;
		case Player::PLAYER_ID::WATSON:
			SkillManager::Get()->GetSkillByID(Skill::SKILL_ID::PISTOL_SHOT)->LevelDown();
			break;
		}
	}
	if (KEY_CON->Down('H'))
		player->ChangeHP(20);
	if (KEY_CON->Down('X'))
		player->GetExp(100.0f);

	EnemySpawner::Get()->Update();
	ItemSpawner::Get()->Update();
	SkillManager::Get()->Update();
	player->Update();
	UIManager::Get()->Update();
	//item->Update();

	//skill->Update();

	//proj->Update();

	//enemy->Update();
	//hpBar->SetSize(Vector2(player->GetHP() / player->GetMaxHP(), 1.0f));
	//hpBar->Update();
}

// Render ¼ø¼­ item ->player->enemy->skill->ui
void TestScene::Render()
{
	//item->Render();
	ItemSpawner::Get()->Render();
	player->Render();
	//skill->Render();
	//proj->Render();

	EnemySpawner::Get()->Render();
	//enemy->Render();
	SkillManager::Get()->Render();
	UIManager::Get()->Render();
	//hpBar->Render();
}

void TestScene::PostRender()
{
	ImGui::Text("The Sprite used is CC-BY-SA licensed.");
	ImGui::Text("Sources1 : https://www.spriters-resource.com/search/?q=holocure");
	ImGui::Text("Sources2 : https://holocure.fandom.com/wiki/HoloCure_Wiki");

	player->PostRender();
	//skill->PostRender();
	
	//EnemySpawner::Get()->PostRneder();
	// enemy->PostRender();
	//hpBar->PostRender();

	SkillManager::Get()->PostRneder();
	ItemSpawner::Get()->PostRneder();
	UIManager::Get()->PostRneder();
}
