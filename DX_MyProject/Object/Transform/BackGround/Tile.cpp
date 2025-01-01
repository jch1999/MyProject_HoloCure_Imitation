#include "framework.h"


vector<shared_ptr<const Frame>>& Tile::GetTileFrames()
{
	static vector<shared_ptr<const Frame>> tileFrames;
	return tileFrames;
}

int& Tile::GetTileUseCnt()
{
	static int tileUseCnt = 0;
	return tileUseCnt;
}

Tile::Tile(int inIdx, Vector2 inRenderSize)
	:BackgroundObject(inRenderSize,1.0f,inIdx)
{
	if (GetTileFrames().empty())
	{
		InitFrame();
	}
	SetMaxIdx(GetTileFrames().size());
	SetIndex(inIdx);

	++GetTileUseCnt();

	is_active = true;
}

Tile::~Tile()
{
	if ((--GetTileUseCnt()) == 0)
	{
		ClearFrame();
	}
}

void Tile::Update()
{
	if (!is_active)return;

	auto& currentFrame = GetTileFrames()[frameIdx];
	scale = currentFrame->GetFrameSize() * renderSize / currentFrame->GetFrameOriginSize();

	WorldUpdate();
}

void Tile::Render()
{
	if (!is_active)return;
	BackgroundObject::Render();

	GetTileFrames()[frameIdx]->Render();
}

void Tile::SetActive(bool active)
{
	is_active = active;
}

void Tile::InitFrame()
{
	auto& tileFrames = GetTileFrames();
	if (!(tileFrames.empty())) return;

	wstring file = L"Textures/Background/PC Computer - HoloCure - Save the Fans - Stage 1 - Grassy Plains_rm_bg.png";

	for (int i = 0; i < 100; i++)
	{
		tileFrames.emplace_back(make_shared<const Frame>(file, 4.0f + i / 10 * 128.0f, 323.0f + i % 10 * 128.0f, 128.0f, 128.0f));
	}
}
void Tile::ClearFrame() 
{
	GetTileFrames().clear();
}
