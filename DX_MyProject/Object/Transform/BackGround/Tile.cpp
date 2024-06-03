#include "framework.h"

Tile::Tile(int idx)
	:idx(idx)
{
	VS = VertexShader::GetInstance(L"Shader/VertexShader/VertexUV.hlsl", 1);
	PS = PixelShader::GetInstance(L"Shader/PixelShader/PixelUV.hlsl");
	CB = new ColourBuffer();

	wstring file = L"Textures/Background/PC Computer - HoloCure - Save the Fans - Stage 1 - Grassy Plains_rm_bg.png";
	vector<Frame*> frames;
	frames.push_back(new Frame(file, 4.0f + idx / 10 * 128.0f, 323.0f + idx % 10 * 128.0f, 128.0f, 128.0f));
	clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP, 1));
	frames.clear();

	is_active = true;
}

Tile::~Tile()
{
}

void Tile::Update()
{
	if (!is_active)return;

	clips[0]->Update();
	scale = clips[0]->GetFrameSize() * Vector2(128.0f,128.0f) / clips[0]->GetFrameOriginSize();

	WorldUpdate();
}

void Tile::Render()
{
	if (!is_active)return;
	VS->Set();
	PS->Set();

	WB->SetVS(0);
	CB->SetPS(0);
	clips[0]->Render();
}

void Tile::PostRender()
{
}

void Tile::SetActive(bool active)
{
	is_active = active;
}
