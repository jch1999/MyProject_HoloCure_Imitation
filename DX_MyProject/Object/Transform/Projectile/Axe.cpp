#include "framework.h"

Axe::Axe(Vector2 size)
	:Projectile()
{
	wstring file = L"Textures/Skill/PC Computer - HoloCure - Save the Fans - Weapons_rm_bg.png";
	Texture* t = Texture::Add(file);

	this->size = size;
	vector<Frame*> frames;
	Vector2 initPos(4.0f, 1616.0f);
	Vector2 frameSize(46.0f, 46.0f);
	/*for (int i = 0; i < 8; i++)
	{
		frames.push_back(new Frame(file, initPos.x + i * 48.0f, initPos.y
			, frameSize.x, frameSize.y));
	}
	clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP, 1 / 8.0f));*/
	frames.push_back(new Frame(file, initPos.x, initPos.y, frameSize.x, frameSize.y));
	clips.push_back(new Clip(frames, Clip::CLIP_TYPE::END, 1.0f));
	clip_idx = 0;

	colliders.push_back(new CircleCollider(size.x * 0.5f));
	colliders.push_back(new CircleCollider(size.x * 0.6f));
	colliders.push_back(new CircleCollider(size.x * 0.72f));
	colliders.push_back(new CircleCollider(size.x * 1.08f));
	collider = colliders[0];

	is_active = false;
	collider->SetActive(false);
}

Axe::~Axe()
{
}

void Axe::Update()
{
	if (nowTime >= lifeTime)
	{
		SetActive(false);
		collider->SetActive(false);
	}
	rot.z += rotSpeed;
	pos += up * speed * DELTA;
	collider->rot.z = rot.z;
	collider->pos = pos;
	collider->WorldUpdate();
	
	nowTime += DELTA;
}

void Axe::Render()
{
	if (!is_active)return;

	VS->Set();
	PS->Set();

	WB->SetVS(0);
	CB->SetPS(0);

	clips[clip_idx]->Render();
	collider->Render();
}

void Axe::PostRender()
{
}

void Axe::respwan()
{
	nowTime = 0.0f;
	nowHitCount = 0;

	WorldUpdate();
	collider->pos = pos;
	collider->WorldUpdate();

	scale = clips[clip_idx]->GetFrameSize() * collider->Size() /
		clips[clip_idx]->GetFrameOriginSize();

	is_active = true;
	collider->SetActive(true);
	rot.z = 0.0f;
}

void Axe::Hit()
{
	nowHitCount++;

	if (nowHitCount == maxHitCount)
	{
		is_active = false;
		nowHitCount = 0;
		return;
	}

}
