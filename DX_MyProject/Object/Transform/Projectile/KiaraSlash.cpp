#include "framework.h"

KiaraSlash::KiaraSlash(Vector2 size)
	:Projectile(20.0f, 200.0f, 1, 2.0f)
	, size(size)
{
	wstring file = L"Textures/Player/PC Computer - HoloCure - Save the Fans - Takanashi Kiara_rm_bg.png";
	Texture* t = Texture::Add(file);

	vector<Frame*> frames;

	// PROJ_STATE::NORMAL
	Vector2 initPos(7.0f, 711.0f);
	Vector2 frame_size(185.0f, 133.0f);
	for (int i = 0; i < 5; i++)
	{
		frames.push_back(new Frame(file, initPos.x + 186.0f * i, initPos.y
			, frame_size.x, frame_size.y));
	}
	clips.push_back(new Clip(frames, Clip::CLIP_TYPE::END, 1.0f / 7.5f));
	frames.clear();

	// PROJ_STATE::AWAKEN
	initPos = Vector2(7.0f, 861.0f);
	frame_size = Vector2(182.0f, 136.0f);
	for (int i = 0; i < 8; i++)
	{
		frames.push_back(new Frame(file, initPos.x + 186.0f * i, initPos.y
			, frame_size.x, frame_size.y));
	}
	clips.push_back(new Clip(frames, Clip::CLIP_TYPE::END, 1.0f / 12.0f));
	frames.clear();

	// 0~2 : PhoenixSword스킬의 기본 collider 설정,
	colliders.push_back(new RectCollider(size));
	colliders.push_back(new RectCollider(size * 1.25f));

	idx_collider;
	collider = colliders[idx_collider];
	collider->pos = pos + move_dir * 50.0f;
}

KiaraSlash::~KiaraSlash()
{

}

void KiaraSlash::Update()
{
	if (!is_active)return;

	// player - kiara와 일정거리에서 이동하지 않음
	// pos += move_dir * speed * DELTA;
	nowTime += DELTA;

	if (nowTime >= lifeTime)
	{
		is_active = false;
		nowTime = 0.0f;
	}

	WorldUpdate();

	collider->pos = pos + move_dir * 20.0f;
	collider->rot.z = this->rot.z;
	collider->WorldUpdate();

	scale = clips[clip_idx]->GetFrameSize() * collider->Size() /
		clips[clip_idx]->GetFrameOriginSize() * Vector2(1.2f,1.0f);

	if (move_dir.x < 0.0f)
		scale = scale * Vector2(-1.0f, 1.0f);

	clips[clip_idx]->Update();
}

void KiaraSlash::Render()
{
	if (!is_active)return;

	VS->Set();
	PS->Set();

	WB->SetVS(0);
	CB->SetPS(0);

	clips[clip_idx]->Render();
	collider->Render();

}

void KiaraSlash::PostRender()
{
	if (!is_active)return;
	ImGui::Text("Now damage : %f", damage);
}

void KiaraSlash::respwan()
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
	clips[clip_idx]->Play();
}
void KiaraSlash::Hit()
{
	// maxHitCount=-1일때는 hit 제한이 없다는 것
	if (maxHitCount == -1)return;

	nowHitCount++;

	if (nowHitCount == maxHitCount)
	{
		is_active = false;
		nowHitCount = 0;
		return;
	}
}