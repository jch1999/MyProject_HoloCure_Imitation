#include "framework.h"

BaelzDice::BaelzDice(Vector2 size)
	:Projectile()
{
	wstring file = L"Textures/Player/PC Computer - HoloCure - Save the Fans - Hakos Baelz_rm_bg.png";
	Texture* t = Texture::Add(file);

	this->size = size;
	vector<Frame*> frames;
	// Normal Dice
	Vector2 initPos(32.0f, 582.0f);
	Vector2 frame_size(18.0f, 18.0f);
	for (int i = 0; i < 6; i++)
	{
		frames.push_back(new Frame(file, initPos.x + 65.0f * i, initPos.y
			, frame_size.x, frame_size.y));
		clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP, 1.0f / 1.0f));
		frames.clear();
	}
	// Awaken Dice
	initPos = Vector2(32.0f, 663.0f);

	for (int i = 0; i < 6; i++)
	{
		frames.push_back(new Frame(file, initPos.x + 65.0f * i, initPos.y
			, frame_size.x, frame_size.y));
		clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP, 1.0f / 1.0f));
		frames.clear();
	}

	for (int i = 0; i < 2; i++)
	{
		RectCollider* collider = new RectCollider(size * (1.0f + i * 0.3f));
		colliders.push_back(collider);
	}

	idx_collider = 0;
	collider = colliders[idx_collider];
	collider->pos = pos;
	clip_idx = 0;
	scale = clips[clip_idx]->GetFrameSize() * collider->Size() /
		clips[clip_idx]->GetFrameOriginSize();

	is_active = false;
	collider->SetActive(false);

}

BaelzDice::~BaelzDice()
{
}

void BaelzDice::Update()
{
	if (!is_active)return;
	
	pos += move_dir * speed * DELTA;
	
	moveDist += (move_dir * speed * DELTA).GetLength();
	if (moveDist >= targetDist) // 다 이동하면 멈춘다
	{
		collider->SetActive(false);
		move_dir = Vector2(0.0f, 0.0f);
		// 다 이동하고 나면 시간 체크를 시작
		nowTime += DELTA;
	}

	if (nowTime >= lifeTime)
	{
		is_active = false;
		moveDist = 0.0f;
		nowTime = 0.0f;
		return;
	}

	WorldUpdate();

	collider->pos = pos;
	collider->rot.z = this->rot.z;
	collider->WorldUpdate();

	scale = clips[clip_idx]->GetFrameSize() * collider->Size() /
		clips[clip_idx]->GetFrameOriginSize();

	clips[clip_idx]->Update();
}

void BaelzDice::Render()
{
	if (!is_active)return;

	VS->Set();
	PS->Set();

	WB->SetVS(0);
	CB->SetPS(0);

	clips[clip_idx]->Render();
	collider->Render();
}

void BaelzDice::PostRender()
{
}

void BaelzDice::respwan()
{
	moveDist = 0.0f;
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

void BaelzDice::Hit()
{
	// maxHitCount=-1일때는 hit 제한이 없다는 것
	if (maxHitCount == -1)return;

	nowHitCount++;

	if (nowHitCount == maxHitCount)
	{
		collider->SetActive(false);
		nowHitCount = 0;
		move_dir = Vector2(0.0f, 0.0f);
		moveDist = 0.0f;
		return;
	}
}