#include "framework.h"

PoisonArea::PoisonArea(Vector2 size)
	:Projectile(20.0f, 200.0f, 1, 2.0f)
	,defaultSize(size)
{
	wstring file = L"Textures/Skill/PC Computer - HoloCure - Save the Fans - Weapons_rm_bg.png";
	Texture* t = Texture::Add(file);

	vector<Frame*> frames;

	// PROJ_STATE::NORMAL
	frames.push_back(new Frame(file, 4.0f, 80.0f, 107.0f, 107.0f));
	clips.push_back(new Clip(frames, Clip::CLIP_TYPE::END, 1.0f));
	frames.clear();

	// 0~2 : SpiderCooking��ų�� �⺻ collider ����,
	// 3~7 : �ܺ� ��ų(Buff)�� ���� ���� ������
	for (int i = 0; i < 8; i++)
	{
		colliders.push_back(new RectCollider(defaultSize * (1.0f + i * 0.2f)));
	}

	idx_collider=0;
	collider = colliders[idx_collider];
	collider->pos = pos;
}

PoisonArea::~PoisonArea()
{
}

void PoisonArea::Update()
{
	if (!is_active)return;

	WorldUpdate();

	collider->pos = pos;
	collider->rot.z = this->rot.z;
	collider->WorldUpdate();

	scale = clips[clip_idx]->GetFrameSize() * collider->Size() /
		clips[clip_idx]->GetFrameOriginSize();

	clips[clip_idx]->Update();
}

void PoisonArea::Render()
{
	if (!is_active)return;

	VS->Set();
	PS->Set();

	WB->SetVS(0);
	CB->SetPS(0);

	clips[clip_idx]->Render();
	collider->Render();
}

void PoisonArea::PostRender()
{
}

void PoisonArea::respwan()
{
	// �� �� Ȱ��ȭ�Ǹ� ��Ȱ���� ���� ����
	return;
}

void PoisonArea::Hit()
{
	// �浹 Ƚ�� ���� ����
	return;
}
