#include "framework.h"

HPBar::HPBar()
	:size(1.0f,1.0f)
{
	wstring file = L"Textures/UI/PC Computer - HoloCure - Save the Fans - Game Menus and HUDs_rm_bg.png";
	vector<Frame*> frames;
	frames.push_back(new Frame(file, -4, 484, 129, 6));
	clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP, 1.0f / 1.0f));
	frames.clear();

	player = UIManager::Get()->GetPlayer();
	scale = clips[0]->GetFrameSize() * size / clips[0]->GetFrameOriginSize();
	id = UI::UI_ID::HP_BAR;
	type = UI::UI_TYPE::BAR;

	is_active = true;
}

HPBar::~HPBar()
{
	delete frame;
}

void HPBar::Update()
{
	if (!is_active || !(target->is_active))return;

	if (player == nullptr)return;
	hpRate = player->GetHP() / player->GetMaxHP();
	scale = clips[0]->GetFrameSize() * Vector2(64, 64) / clips[0]->GetFrameOriginSize() * Vector2(size.x * hpRate, size.y);

	pos = player->pos + offset;
	WorldUpdate();
	clips[0]->Update();
}

void HPBar::Render()
{
	if (!is_active || !(target->is_active))return;
	if (player == nullptr || hpRate>0.95f)return;
	clips[0]->Render();
}

void HPBar::PostRender()
{
}

void HPBar::Respawn()
{
}
