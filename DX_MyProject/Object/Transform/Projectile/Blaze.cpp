#include "framework.h"

Blaze::Blaze(Vector2 size)
	:Projectile(20.0f, 200.0f, 1, 2.0f)
	, size(size)
{
	wstring file = L"Textures/Player/PC Computer - HoloCure - Save the Fans - Takanashi Kiara_rm_bg.png";
	Texture* t = Texture::Add(file);

	vector<Frame*> frames;
	Vector2 initPos(7.0f, 3736.0f);
	Vector2 frameSize(38.0f,38.0f);
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

Blaze::~Blaze()
{
}

void Blaze::Update()
{
	if (!is_active)return;
	
	nowTime += DELTA;


	WorldUpdate();

	collider->pos = pos;
	collider->rot.z = this->rot.z;
	collider->WorldUpdate();

	scale = clips[clip_idx]->GetFrameSize() * size /
		clips[clip_idx]->GetFrameOriginSize() * 1.5f;

	clips[clip_idx]->Update();
	if (nowTime >= lifeTime)
		is_active = false;
}

void Blaze::Render()
{
	if (!is_active)return;

	VS->Set();
	PS->Set();

	WB->SetVS(0);
	CB->SetPS(0);

	clips[clip_idx]->Render();
	collider->Render();
}

void Blaze::PostRender()
{
	if (!is_active)return;
	// ImGui::Text("Blaze pos : ", (float*)&pos, -WIN_WIDTH, WIN_WIDTH);
	ImGui::Text("Blaze damage : %f", damage);
}

void Blaze::respwan()
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

void Blaze::Hit()
{
	nowHitCount++;

	if (nowHitCount == maxHitCount)
	{
		is_active = false;
		nowHitCount = 0;
		return;
	}
}