#include "framework.h"

LavaBucket::LavaBucket(Vector2 size)
	:Projectile()
{
	wstring file = L"Textures/Skill/PC Computer - HoloCure - Save the Fans - Weapons_rm_bg.png";
	Texture* t = Texture::Add(file);

	this->size = size;
	vector<Frame*> frames;
	// Lava Start
	Vector2 initPos(176.0f, 193.0f);
	Vector2 frameSize(17.0f, 20.0f);
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			frames.push_back(new Frame(file, initPos.x + j * 129.0f, initPos.y+i*129.0f
				, frameSize.x, frameSize.y));
		}
	}
	clips.push_back(new Clip(frames, Clip::CLIP_TYPE::END, 1 / 9.0f));
	frames.clear();

	clip_idx = 0;

	colliders.push_back(new RectCollider(size));
	collider = colliders[0];

	lava = new LavaArea();

	is_active = false;
	collider->SetActive(false);
}

LavaBucket::~LavaBucket()
{
}

void LavaBucket::Update()
{
	if (!(is_active || lava->is_active))return;
	if (lifeTime > nowTime)
	{
		nowTime += DELTA;
	}
	else
	{
		lava->respwan();
	}
	if (is_active)
	{
		pos += move_dir * speed * DELTA;

		WorldUpdate();
		collider->pos = pos;
		collider->WorldUpdate();
	}
	if (lava->is_active)
	{
		lava->Update();
	}
}

void LavaBucket::Render()
{
	if (!is_active)return;

	VS->Set();
	PS->Set();

	WB->SetVS(0);
	CB->SetPS(0);

	clips[clip_idx]->Render();
	collider->Render();
}

void LavaBucket::PostRender()
{
}

void LavaBucket::respwan()
{
	nowTime = 0.0f;
	nowHitCount = 0;

	WorldUpdate();
	collider->pos = pos;
	collider->WorldUpdate();
	scale = clips[clip_idx]->GetFrameSize() * collider->Size() /
		clips[clip_idx]->GetFrameOriginSize();

	clip_idx = 0;
	clips[clip_idx]->Play();

	is_active = true;
	collider->SetActive(true);
}

void LavaBucket::Hit()
{
	nowHitCount++;

	if (nowHitCount == maxHitCount)
	{
		is_active = false;
		nowHitCount = 0;
		return;
	}

}

void LavaBucket::OnCollision()
{
	
}
