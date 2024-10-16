#include "framework.h"

LavaArea::LavaArea(ProjectileSize projSize)
	:Projectile(projSize)
{
	wstring file = L"Textures/Skill/PC Computer - HoloCure - Save the Fans - Weapons_rm_bg.png";
	Texture* t = Texture::Add(file);

	vector<Frame*> frames;
	// Lava Start
	Vector2 initPos(4.0f, 243.0f);
	Vector2 frameSize(127.0f, 127.0f);
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			frames.push_back(new Frame(file, initPos.x + j * 129.0f, initPos.y + i * 129.0f
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

LavaArea::~LavaArea()
{
}

void LavaArea::Update()
{
}

void LavaArea::Render()
{
}

void LavaArea::PostRender()
{
}

void LavaArea::OnCollision()
{
}

void LavaArea::respwan()
{
}

void LavaArea::Hit()
{
}
