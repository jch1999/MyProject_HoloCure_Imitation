#include "framework.h"

TestScene::TestScene()
{
	player = new Watson();
	player->pos = WIN_CENTER;
	CAM->SetTarget(player);

	BackGroundManager::Get()->SetPlayer(player);
	ItemSpawner::Get()->SetPlayer(player);
	EnemySpawner::Get()->SetPlayer(player);
	SkillManager::Get()->SetPlayer(player);
	UIManager::Get()->SetPlayer(player);
	player->GetExp(0);
	player->CheckMoveDir();
}

TestScene::~TestScene()
{
	delete player;
	BackGroundManager::Delete();
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
		player->GetExp(1000.0f);
	if (KEY_CON->Down('S'))
		ItemSpawner::Get()->GenerateItem(player->pos + Vector2(50.0f, 50.0f), Item::ITEM_ID::ANVIL, ItemSpawner::Get()->anvilUseCnt);
	if (KEY_CON->Down('G'))
		ItemSpawner::Get()->GenerateItem(player->pos + Vector2(50.0f, 50.0f), Item::ITEM_ID::REWORD_BOX, ItemSpawner::Get()->coinValue);
	
	if (KEY_CON->Down('C'))
		ItemSpawner::Get()->nowCoinValue += 100.0f;
	BackGroundManager::Get()->Update();
	EnemySpawner::Get()->Update();
	ItemSpawner::Get()->Update();
	SkillManager::Get()->Update();
	player->Update();
	UIManager::Get()->Update();
}

// Render ¼ø¼­ item ->player->enemy->skill->ui
void TestScene::Render()
{
	BackGroundManager::Get()->BeforeRender();
	ItemSpawner::Get()->Render();
	BackGroundManager::Get()->Render();
	player->Render();
	EnemySpawner::Get()->Render();
	BackGroundManager::Get()->AfterRender();
	SkillManager::Get()->Render();
	UIManager::Get()->Render();
}

void TestScene::PostRender()
{
	ImGui::Text("The Sprite used is CC-BY-SA licensed.");
	ImGui::Text("Sources1 : https://www.spriters-resource.com/search/?q=holocure");
	ImGui::Text("Sources2 : https://holocure.fandom.com/wiki/HoloCure_Wiki");
	ImGui::Text("Cam's pos : %f %f", CAM->pos.x, CAM->pos.y);
	//player->PostRender();

	SkillManager::Get()->PostRneder();
	//ItemSpawner::Get()->PostRneder();
	UIManager::Get()->PostRneder();
}
