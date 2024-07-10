#include "framework.h"

PoisonArea::PoisonArea(Vector2 size)
	:Projectile(20.0f, 200.0f, 1, 2.0f)
	,defaultSize(size)
{
	wstring file = L"Textures/Skill/PC Computer - HoloCure - Save the Fans - Weapons_rm_bg.png";
	Texture* t = Texture::Add(file);

	vector<Frame*> frames;

	// PROJ_STATE::NORMAL
	frames.push_back(new Frame(file, 4.0f, 80.0f, 107.0f, 107.0f));
	clips.push_back(new Clip(frames, Clip::CLIP_TYPE::END, 1.0f));
	frames.clear();

	// 0~2 : SpiderCooking스킬의 기본 collider 설정,
	colliders.push_back(new CircleCollider(defaultSize.x * 0.5f));
	colliders.push_back(new CircleCollider(defaultSize.x * 0.5f * 1.15f)); // SpiderCooking LV 2
	colliders.push_back(new CircleCollider(defaultSize.x * 0.5f * 1.25f)); // SpiderCooking LV 4

	idx_collider=0;
	collider = colliders[idx_collider];
	collider->pos = pos;
	CB->data.colour = Float4(1.0f, 1.0f, 1.0f, 0.5f);
}

PoisonArea::~PoisonArea()
{
}

void PoisonArea::Update()
{
	if (!is_active)return;

	WorldUpdate();

	collider->pos = pos;
	collider->WorldUpdate();

	scale = clips[clip_idx]->GetFrameSize() * collider->Size() /
		clips[clip_idx]->GetFrameOriginSize();

	clips[clip_idx]->Update();
}

void PoisonArea::Render()
{
	if (!is_active)return;

	VS->Set();
	PS->Set();

	WB->SetVS(0);
	CB->SetPS(0);

	clips[clip_idx]->Render();
	collider->Render();
}

void PoisonArea::PostRender()
{
}

void PoisonArea::respwan()
{
	// 한 번 활성화되면 재활성될 일은 없음
	return;
}

void PoisonArea::Hit()
{
	// 충돌 횟수 제한 없음
	return;
}
