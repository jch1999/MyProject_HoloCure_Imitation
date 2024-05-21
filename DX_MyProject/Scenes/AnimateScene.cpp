#include "framework.h"

AnimateScene::AnimateScene()
{
	player = new AnimatePlayer();
	player->pos = Vector2(WIN_CENTER_X, WIN_CENTER_Y);
}

AnimateScene::~AnimateScene()
{
	delete player;
}

void AnimateScene::Update()
{
	player->Update();
}

void AnimateScene::Render()
{
	player->Render();
}

void AnimateScene::PostRender()
{
}
