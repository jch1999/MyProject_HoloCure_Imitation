#include "framework.h"

vector<shared_ptr<const Frame>> LavaBucket::labaBucketFrames;
int LavaBucket::labaBucketUseCnt = 0;

LavaBucket::LavaBucket(ProjectileSize projSize)
	:Projectile(projSize)
{
	if (labaBucketFrames.empty())
	{
		Init();
	}

	clips.push_back(make_shared<Clip>(labaBucketFrames, Clip::CLIP_TYPE::END, 1 / 9.0f));

	clipIdx = 0;

	colliders.push_back(new RectCollider(size));
	collider = colliders[0];

	lava = new LavaArea();

	is_active = false;
	collider->SetActive(false);

	++labaBucketUseCnt;
}

LavaBucket::~LavaBucket()
{
	if ((--labaBucketUseCnt) == 0)
	{
		labaBucketFrames.clear();
	}
}

void LavaBucket::Init()
{
	if (!labaBucketFrames.empty()) return;

	wstring file = L"Textures/Skill/PC Computer - HoloCure - Save the Fans - Weapons_rm_bg.png";

	// ?? 이게 왜 필요하지? 이 클래스는 용암 양동이 인데? 작업 내역을 확인하고 수정 진행
	// Lava Start
	Vector2 initPos(176.0f, 193.0f);
	Vector2 frameSize(17.0f, 20.0f);
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			labaBucketFrames.push_back(make_shared<const Frame>(file, initPos.x + j * 129.0f, initPos.y + i * 129.0f
				, frameSize.x, frameSize.y));
		}
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

	clips[clipIdx]->Render();
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
