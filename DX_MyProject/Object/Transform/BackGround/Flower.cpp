#include "framework.h"

vector<shared_ptr<const Frame>>& Flower::GetFlowerFrames()
{
	static vector<shared_ptr<const Frame>> flowerFrames;
	return flowerFrames;
}

int& Flower::GetFlowerUseCnt()
{
	static int flowerUseCnt = 0;
	return flowerUseCnt;
}

Flower::Flower(Vector2 inRenderSize,float inSpawnRate)
	:BackgroundObject(inRenderSize,inSpawnRate)
{
	if (GetFlowerFrames().empty())
	{
		InitFrame();
	}

	SetMaxIdx(GetFlowerFrames().size());

	ChangePos();

	++GetFlowerUseCnt();
}

Flower::~Flower()
{
	delete CB;

	if ((--GetFlowerUseCnt()) == 0)
	{
		ClearFrame();
	}
}

void Flower::Update()
{
	auto& currentFrame = GetFlowerFrames()[frameIdx];
	scale = currentFrame->GetFrameSize() * renderSize / currentFrame->GetFrameOriginSize();
	
	Vector2 before_pos = pos;
	pos = target->pos + offset;
	WorldUpdate();

	if ((before_pos - pos).GetLength() > 1.0f)
	{
		ChangePos();
	}
}

void Flower::Render()
{
	if (!is_active)return;
	BackgroundObject::Render();

	GetFlowerFrames()[frameIdx]->Render();
}

void Flower::InitFrame()
{
	auto& flowerFrames = GetFlowerFrames();
	if (!(flowerFrames.empty())) return;

	wstring file = L"Textures/Background/PC Computer - HoloCure - Save the Fans - Stage 1 - Grassy Plains_rm_bg.png";

	for (int i = 0; i < 6; i++)
	{
		flowerFrames.emplace_back(make_shared<const Frame>(file, 4.0f + 31.0f * i, 74.0f, 29.0f, 38.0f));
	}
}

void Flower::ClearFrame()
{
	GetFlowerFrames().clear();
}
