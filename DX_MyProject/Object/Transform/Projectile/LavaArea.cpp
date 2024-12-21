#include "framework.h"

vector<vector<shared_ptr<const Frame>>> LavaArea::lavaAreaFrames;
int LavaArea::lavaAreaUseCnt = 0;

LavaArea::LavaArea(ProjectileSize projSize)
	:Projectile(projSize)
{
	if (lavaAreaFrames.empty())
	{
		Init();
	}

	for (int i = 0; i < lavaAreaFrames.size(); i++)
	{
		clips.push_back(make_shared<Clip>(lavaAreaFrames[i], Clip::CLIP_TYPE::END, 1 / 9.0f));
	}
	clipIdx = 0;

	colliders.push_back(new RectCollider(size));
	collider = colliders[0];

	is_active = false;
	collider->SetActive(false);

	++lavaAreaUseCnt;
}

LavaArea::~LavaArea()
{
	if ((--lavaAreaUseCnt) == 0)
	{
		lavaAreaFrames.clear();
	}
}

void LavaArea::Init()
{
	if (!lavaAreaFrames.empty()) return;

	wstring file = L"Textures/Skill/PC Computer - HoloCure - Save the Fans - Weapons_rm_bg.png";

	// Lava Star
	Vector2 initPos(4.0f, 243.0f);
	Vector2 frameSize(127.0f, 127.0f);
	{
		vector<shared_ptr<const Frame>> startFrames;
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				startFrames.push_back(make_shared<Frame>(file, initPos.x + j * 129.0f, initPos.y + i * 129.0f
					, frameSize.x, frameSize.y));
			}
		}
		lavaAreaFrames.push_back(startFrames);
	}
	// Lava Loop
	initPos = Vector2(395.0f, 243.0f);
	{
		vector<shared_ptr<const Frame>> loopFrames;
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				loopFrames.push_back(make_shared<Frame>(file, initPos.x + j * 129.0f, initPos.y + i * 129.0f
					, frameSize.x, frameSize.y));
				if (i == 5 && j == 1)
					break;
			}
		}
		lavaAreaFrames.push_back(loopFrames);
	}
	// Lava End
	initPos = Vector2(4.0f, 656.0f);
	{
		vector<shared_ptr<const Frame>> endFrames;
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				endFrames.push_back(make_shared<Frame>(file, initPos.x + j * 129.0f, initPos.y + i * 129.0f
					, frameSize.x, frameSize.y));
			}
		}
		lavaAreaFrames.push_back(endFrames);
	}
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
