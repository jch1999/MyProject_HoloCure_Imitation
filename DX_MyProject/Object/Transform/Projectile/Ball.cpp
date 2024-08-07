#include "framework.h"

Ball::Ball(Vector2 size)
	:Projectile()
{
	wstring file = L"Textures/Skill/PC Computer - HoloCure - Save the Fans - Weapons_rm_bg.png";
	Texture* t = Texture::Add(file);

	this->size = size;
	vector<Frame*> frames;
	frames.push_back(new Frame(file, 4.0f, 3425.0f, 41.0f, 41.0f));
	clips.push_back(new Clip(frames, Clip::CLIP_TYPE::END, 1 / 4.0f));
	clip_idx = 0;

	colliders.push_back(new CircleCollider(size.x));
	collider = colliders[0];

	is_active = false;
	collider->SetActive(false);
}

Ball::~Ball()
{
}

void Ball::Update()
{
	if (lifeTime > 0.0f)
	{
		lifeTime -= DELTA;
	}
	else
		is_active = false;

	velocity += Vector2(0, GRAVITY) * DELTA;
	pos = pos + velocity * speed * DELTA;
	WorldUpdate();

	collider->pos = pos;
	collider->WorldUpdate();
}

void Ball::Render()
{
	if (!is_active)return;

	VS->Set();
	PS->Set();

	WB->SetVS(0);
	CB->SetPS(0);

	clips[clip_idx]->Render();
	collider->Render();
}

void Ball::PostRender()
{
}

void Ball::respwan()
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
}

void Ball::Hit()
{
	/*nowHitCount++;

	if (nowHitCount == maxHitCount)
	{
		is_active = false;
		nowHitCount = 0;
		return;
	}*/

}

void Ball::AddVelocity(Vector2 newVel)
{
}
