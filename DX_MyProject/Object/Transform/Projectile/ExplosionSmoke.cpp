#include "framework.h"

ExplosionSmoke::ExplosionSmoke(Vector2 size)
	:Projectile(20.0f, 200.0f, 1, 2.0f)
	, size(size)
{
	wstring file = L"Textures/Skill/PC Computer - HoloCure - Save the Fans - Weapons_rm_bg.png";
	Texture* t = Texture::Add(file);

	vector<Frame*> frames;
	Vector2 initPos(4.0f, 1194.0f);
	Vector2 frameSize(128.0f, 128.0f);
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			frames.push_back(new Frame(file, initPos.x + j * 130.0f, initPos.y + i * 130.0f
				, frameSize.x, frameSize.y));
			if (i == 2 && j == 2)
				break;
		}
	}
	clips.push_back(new Clip(frames, Clip::CLIP_TYPE::END, 1 / 12.0f));
	clip_idx = 0;

	colliders.push_back(new RectCollider(size));
	colliders.push_back(new RectCollider(size*1.15f));
	colliders.push_back(new RectCollider(size*1.2f));
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

	scale = clips[clip_idx]->GetFrameSize() * collider->Size() /
		clips[clip_idx]->GetFrameOriginSize();

	clips[clip_idx]->Update();
	if (clips[clip_idx]->GetFrameNum() == (clips[clip_idx]->GetFrameCnt() - 1))
	{
		is_active = false;
		collider->SetActive(false);
	}
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

bool ExplosionSmoke::isDamageAble()
{
	return is_active&&(clips[clip_idx]->GetFrameNum()<clips[clip_idx]->GetFrameCnt()/5);
}
