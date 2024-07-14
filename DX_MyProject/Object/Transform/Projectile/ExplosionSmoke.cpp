#include "framework.h"

ExplosionSmoke::ExplosionSmoke(Vector2 size)
	:Projectile(20.0f, 200.0f, 1, 2.0f)
	, size(size)
{
	wstring file = L"Textures/Skill/PC Computer - HoloCure - Save the Fans - Weapons_rm_bg.png";
	Texture* t = Texture::Add(file);

	vector<Frame*> frames;
	Vector2 initPos(7.0f, 3736.0f);
	Vector2 frameSize(38.0f, 38.0f);
	for (int i = 0; i < 4; i++)
	{
		frames.push_back(new Frame(file, initPos.x + i * 39.0f, initPos.y
			, frameSize.x, frameSize.y));
	}
	clips.push_back(new Clip(frames, Clip::CLIP_TYPE::PINGPONG, 1 / 4.0f));
	clip_idx = 0;

	colliders.push_back(new RectCollider(size));
	collider = colliders[0];

	is_active = false;
	collider->SetActive(false);
}

ExplosionSmoke::~ExplosionSmoke()
{
}

void ExplosionSmoke::Update()
{
	if (!is_active)return;

	WorldUpdate();

	collider->pos = pos;
	collider->rot.z = this->rot.z;
	collider->WorldUpdate();

	scale = clips[clip_idx]->GetFrameSize() * size /
		clips[clip_idx]->GetFrameOriginSize() * 1.5f;

	clips[clip_idx]->Update();
}

void ExplosionSmoke::Render()
{
	if (!is_active)return;

	VS->Set();
	PS->Set();

	WB->SetVS(0);
	CB->SetPS(0);

	clips[clip_idx]->Render();
	collider->Render();
}

void ExplosionSmoke::PostRender()
{
}

void ExplosionSmoke::respwan()
{
	WorldUpdate();
	collider->pos = pos;
	collider->WorldUpdate();
	scale = clips[clip_idx]->GetFrameSize() * collider->Size() /
		clips[clip_idx]->GetFrameOriginSize();

	SetActive(true);
	collider->SetActive(true);
	clips[clip_idx]->Play();
}

void ExplosionSmoke::Hit()
{
}
