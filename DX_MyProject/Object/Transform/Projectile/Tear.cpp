#include "framework.h"

Tear::Tear(Vector2 size)
	:Projectile()
{
	wstring file = L"Textures/Skill/PC Computer - HoloCure - Save the Fans - Weapons_rm_bg.png";
	Texture* t = Texture::Add(file);

	this->size = size;
	vector<Frame*> frames;
	frames.push_back(new Frame(file, 4.0f, 946.0f, 10.0f, 8.0f));
	clips.push_back(new Clip(frames, Clip::CLIP_TYPE::PINGPONG, 1 / 4.0f));
	clip_idx = 0;

	colliders.push_back(new RectCollider(size));
	collider = colliders[0];

	is_active = false;
	collider->SetActive(false);
}

Tear::~Tear()
{
}

void Tear::Update()
{
}

void Tear::Render()
{
	if (!is_active)return;

	VS->Set();
	PS->Set();

	WB->SetVS(0);
	CB->SetPS(0);

	clips[clip_idx]->Render();
	collider->Render();
}

void Tear::PostRender()
{
}

void Tear::respwan()
{
}

void Tear::Hit()
{
}
