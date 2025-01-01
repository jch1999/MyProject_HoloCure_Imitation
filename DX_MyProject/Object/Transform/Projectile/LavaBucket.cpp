#include "framework.h"

shared_ptr<const Frame>& LavaBucket::GetLabaBucketFrame()
{
	static shared_ptr<const Frame> lavaBucketFrame;;
	return lavaBucketFrame;
}

int& LavaBucket::GetLabaBucketUseCnt()
{
	static int labaBucketUseCnt = 0;
	return labaBucketUseCnt;
}

LavaBucket::LavaBucket(ProjectileSize projSize)
	:Projectile(projSize)
{
	if (!GetLabaBucketFrame())
	{
		InitFrame();
	}

	colliders.push_back(new RectCollider(size));
	collider = colliders[0];

	lava = new LavaArea();

	is_active = false;
	collider->SetActive(false);

	++GetLabaBucketUseCnt();
}

LavaBucket::~LavaBucket()
{
	if ((--GetLabaBucketUseCnt()) == 0)
	{
		ClearFrame();
	}
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
		pos += moveDir * speed * DELTA;

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

	GetLabaBucketFrame()->Render();
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
	scale = clips[clipIdx]->GetFrameSize() * collider->Size() /
		clips[clipIdx]->GetFrameOriginSize();

	clipIdx = 0;
	clips[clipIdx]->Play();

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

void LavaBucket::InitFrame()
{
	auto& lavaBucketFrame = GetLabaBucketFrame();
	if (!lavaBucketFrame) return;

	wstring file = L"Textures/Skill/PC Computer - HoloCure - Save the Fans - Weapons_rm_bg.png";

	lavaBucketFrame = make_shared<const Frame>(file, 0.0f, 0.0f, 0.0f, 0.0f);
}

void LavaBucket::ClearFrame()
{
	GetLabaBucketFrame().reset();
}