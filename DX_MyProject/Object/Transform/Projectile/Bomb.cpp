#include "framework.h"

Bomb::Bomb(Vector2 size, float targetDist, Vector2 move_dir)
	:Projectile(20.0f, 200.0f, 1, 2.0f)
	, size(size)
{
	this->targetDist = targetDist;
	this->move_dir = move_dir;
	wstring file = L"Textures/Skill/PC Computer - HoloCure - Save the Fans - Weapons_rm_bg.png";
	Texture* t = Texture::Add(file);

	vector<Frame*> frames;
	frames.push_back(new Frame(file, 416.0f, 1508.0f, 23.0f, 29.0f));
	clips.push_back(new Clip(frames, Clip::CLIP_TYPE::END, 1));
	clip_idx = 0;

	colliders.push_back(new RectCollider(size * Vector2(1.2f, 1.2f)));
	collider = colliders[0];

	is_active = false;
	collider->SetActive(false);
}

Bomb::~Bomb()
{
}

void Bomb::Update()
{
	if (!is_active)return;

	pos = LERP(pos, targetPos, speed * DELTA);
	if ((pos-targetPos).GetLength()<0.1f)
	{
		pos = targetPos;
	}

	WorldUpdate();

	collider->pos = pos;
	collider->WorldUpdate();

	scale = clips[clip_idx]->GetFrameSize() * collider->Size() /
		clips[clip_idx]->GetFrameOriginSize();

	clips[clip_idx]->Update();
}

void Bomb::Render()
{
	if (!is_active)return;

	VS->Set();
	PS->Set();

	WB->SetVS(0);
	CB->SetPS(0);

	clips[clip_idx]->Render();
	collider->Render();
}

void Bomb::PostRender()
{
}

void Bomb::respwan()
{
	WorldUpdate();
	collider->pos = pos;
	collider->WorldUpdate();
	scale = clips[clip_idx]->GetFrameSize() * collider->Size() /
		clips[clip_idx]->GetFrameOriginSize();

	moveDist = 0.0f;
	SetActive(true);
	collider->SetActive(true);
}

void Bomb::Hit()
{
	SetActive(false);
	collider->SetActive(false);
}
