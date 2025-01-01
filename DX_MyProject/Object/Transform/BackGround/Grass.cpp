#include "framework.h"


vector<shared_ptr<const Frame>>& Grass::GetGrassFrames()
{
	static vector<shared_ptr<const Frame>> grassFrames;
	return grassFrames;
}

int& Grass::GetGrassUseCnt()
{
	static int grassUseCnt = 0;
	return grassUseCnt;
}

Grass::Grass(Vector2 inRenderSize,float inSpawnRate)
	:BackgroundObject(inRenderSize,inSpawnRate)
{
	if (GetGrassFrames().empty())
	{
		InitFrame();
	}
	SetMaxIdx(GetGrassFrames().size());

	ChangePos();

	++GetGrassUseCnt();
}

Grass::~Grass()
{
	if ((--GetGrassUseCnt()) == 0)
	{
		ClearFrame();
	}
}

void Grass::Update()
{
	auto& currentFrame = GetGrassFrames()[frameIdx];
	scale = currentFrame->GetFrameSize() * renderSize / currentFrame->GetFrameOriginSize();
	
	Vector2 before_pos = pos;
	pos = target->pos + offset;
	WorldUpdate();

	if ((before_pos - pos).GetLength() > 1.0f)
	{
		ChangePos();
	}
}

void Grass::Render()
{
	if (!is_active)return;
	BackgroundObject::Render();

	GetGrassFrames()[frameIdx]->Render();
}


void Grass::InitFrame()
{
	auto& grassFrames = GetGrassFrames();
	if (!(grassFrames.empty())) return;

	wstring file = L"Textures/Background/PC Computer - HoloCure - Save the Fans - Stage 1 - Grassy Plains_rm_bg.png";

	for (int i = 0; i < 2; i++)
	{
		grassFrames.emplace_back(make_shared<const Frame>(file, 190.0f + 31.0f * i, 74.0f, 29.0f, 30.0f));
	}
}

void Grass::ClearFrame()
{
	GetGrassFrames().clear();
}


