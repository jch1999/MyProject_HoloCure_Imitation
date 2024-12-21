#include "framework.h"

vector<shared_ptr<const Frame>> Tile::TileFrames;
int Tile::TileUseCnt = 0;

Tile::Tile(int idx)
	:idx(idx)
{
	VS = VertexShader::GetInstance(L"Shader/VertexShader/VertexUV.hlsl", 1);
	PS = PixelShader::GetInstance(L"Shader/PixelShader/PixelUV.hlsl");
	CB = new ColourBuffer();

	if (TileFrames.empty())
	{
		Init();
	}

	frame = GetFrame(idx);
	++TileUseCnt;

	is_active = true;
}

Tile::~Tile()
{
	if ((--TileUseCnt) == 0)
	{
		TileFrames.clear();
	}
}

void Tile::Update()
{
	if (!is_active)return;

	scale = frame->GetFrameSize() * Vector2(128.0f,128.0f) / frame->GetFrameOriginSize();

	WorldUpdate();
}

void Tile::Init()
{
	TileFrames.clear();

	wstring file = L"Textures/Background/PC Computer - HoloCure - Save the Fans - Stage 1 - Grassy Plains_rm_bg.png";

	for (int i = 0; i < 100; i++)
	{
		TileFrames.push_back(make_shared<const Frame>(file, 4.0f + idx / 10 * 128.0f, 323.0f + idx % 10 * 128.0f, 128.0f, 128.0f));
	}
}

void Tile::Render()
{
	if (!is_active)return;
	VS->Set();
	PS->Set();

	WB->SetVS(0);
	CB->SetPS(0);
	frame->Render();
}

void Tile::PostRender()
{
}

void Tile::SetActive(bool active)
{
	is_active = active;
}
