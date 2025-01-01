#include "framework.h"

PlayScene::PlayScene()
{
	player = new Baelz();
	player->pos = WIN_CENTER;

	CAM->SetTarget(player);

	BackgroundManager::Get()->SetPlayer(player);
	ItemSpawner::Get()->SetPlayer(player);
	EnemySpawner::Get()->SetPlayer(player);
	SkillManager::Get()->SetPlayer(player);
	UIManager::Get()->SetPlayer(player);

	player->GetExp(0);
	player->CheckMoveDir();
}

PlayScene::~PlayScene()
{
	delete player;
	BackgroundManager::Delete();
	EnemySpawner::Delete();
	SkillManager::Delete();
	UIManager::Delete();
}

void PlayScene::Update()
{
	BackgroundManager::Get()->Update();
	EnemySpawner::Get()->Update();
	ItemSpawner::Get()->Update();
	SkillManager::Get()->Update();
	player->Update();
	UIManager::Get()->Update();
}

void PlayScene::Render()
{
	BackgroundManager::Get()->BeforeRender();
	ItemSpawner::Get()->Render();
	BackgroundManager::Get()->Render();
	player->Render();
	EnemySpawner::Get()->Render();
	BackgroundManager::Get()->AfterRender();
	SkillManager::Get()->Render();
	UIManager::Get()->Render();
}

void PlayScene::PostRender()
{
	ImGui::Text("The Sprite used is CC-BY-SA licensed.");
	ImGui::Text("Sources1 : https://www.spriters-resource.com/search/?q=holocure");
	ImGui::Text("Sources2 : https://holocure.fandom.com/wiki/HoloCure_Wiki");
}
