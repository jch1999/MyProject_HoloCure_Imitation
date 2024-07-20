#include "framework.h"

LavaBucket::LavaBucket(Vector2 size)
	:Projectile()
{
	wstring file = L"Textures/Skill/PC Computer - HoloCure - Save the Fans - Weapons_rm_bg.png";
	Texture* t = Texture::Add(file);

	this->size = size;
	vector<Frame*> frames;
	// Lava Start
	Vector2 initPos(4.0f, 243.0f);
	Vector2 frameSize(127.0f, 127.0f);
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
	// Lava Loop
	initPos = Vector2(395.0f, 243.0f);
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			frames.push_back(new Frame(file, initPos.x + j * 129.0f, initPos.y + i * 129.0f
				, frameSize.x, frameSize.y));
			if (i == 5 && j == 1)
				break;
		}
	}
	clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP, 1 / 14.0f));
	frames.clear();
	// Lava End
	initPos = Vector2(4.0f, 656.0f);
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			frames.push_back(new Frame(file, initPos.x + j * 129.0f, initPos.y + i * 129.0f
				, frameSize.x, frameSize.y));
		}
	}
	clips.push_back(new Clip(frames, Clip::CLIP_TYPE::END, 1 / 9.0f));
	frames.clear();

	clip_idx = 0;

	colliders.push_back(new RectCollider(size));
	collider = colliders[0];

	is_active = false;
	collider->SetActive(false);
}

LavaBucket::~LavaBucket()
{
}

void LavaBucket::Update()
{
	if (!is_active)return;
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
