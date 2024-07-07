#include "framework.h"

WatsonBullet::WatsonBullet(Vector2 size)
	:Projectile(20.0f,200.0f,1,2.0f)
	,size(size)
{
	wstring file = L"Textures/Player/PC Computer - HoloCure - Save the Fans - Amelia Watson_rm_bg.png";
	Texture* t = Texture::Add(file);
	
	vector<Frame*> frames;
	frames.push_back(new Frame(file, 18, 1047, 10, 8));
	frames.push_back(new Frame(file, 51, 1047, 10, 8));

	clips.push_back(new Clip(frames, Clip::CLIP_TYPE::PINGPONG, 1.0f / 8.0f));
	clip_idx = 0;

	colliders.push_back(new RectCollider(size));
	colliders[0]->SetActive(false);
	collider = colliders[0];
	collider->pos = pos;
	

	is_active = false;
}

WatsonBullet::~WatsonBullet()
{

}

void WatsonBullet::Update()
{
	if (!is_active)return;

	pos += move_dir * speed * DELTA;
	nowTime += DELTA;

	if (nowTime >= lifeTime)
	{
		is_active = false;
		nowTime = 0.0f;
	}

	WorldUpdate();

	collider->pos = pos;
	collider->rot.z = this->rot.z;
	collider->WorldUpdate();

	// watsonBullet은 normal과 awaken의 애니메이션 차이가 없음
	scale = clips[clip_idx]->GetFrameSize() * size /
		clips[clip_idx]->GetFrameOriginSize();
	clips[clip_idx]->Update();
}

void WatsonBullet::Render()
{
	if (!is_active)return;

	VS->Set();
	PS->Set();

	WB->SetVS(0);
	CB->SetPS(0);

	clips[clip_idx]->Render();
	collider->Render();

}

void WatsonBullet::PostRender()
{
	if (!is_active)return;
}

void WatsonBullet::respwan()
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

void WatsonBullet::Hit()
{
	nowHitCount++;

	if (nowHitCount == maxHitCount)
	{
		is_active = false;
		nowHitCount = 0;
		return;
	}
}