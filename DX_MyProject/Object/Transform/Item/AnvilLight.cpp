#include "framework.h"

AnvilLight::AnvilLight(Vector2 pos)
	:size(Vector2(55.0f,105.0f)*1.5f)
	,offset(Vector2(0.0f,-45.0f))
{
	VS = VertexShader::GetInstance(L"Shader/VertexShader/VertexUV.hlsl", 1);
	PS = PixelShader::GetInstance(L"Shader/PixelShader/PixelUV.hlsl");
	CB = new ColourBuffer();

	this->pos = pos + offset;

	wstring file = L"Textures/Item/PC Computer - HoloCure - Save the Fans - Pickups_rm_bg.png";
	Texture* t = Texture::Add(file);

	vector<Frame*> frames;
	// backlight clip
	frames.push_back(new Frame(file, 205.0f, 144.0f, 55.0f, 105.0f));
	clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP, 1.0f / 1.0f));
	frames.clear();

	CB->data.colour = Float4(1.0f, 1.0f, 1.0f, 0.85f);
	is_active = false;
}

AnvilLight::~AnvilLight()
{
	delete CB;
	for (auto c : clips)
		delete c;
}

void AnvilLight::Update()
{
	if (!is_active)return;
	WorldUpdate();
	clips[0]->Update();

	scale = clips[clip_idx]->GetFrameSize() * size /
		clips[clip_idx]->GetFrameOriginSize();
}

void AnvilLight::Render()
{
	if (!is_active)return;
	
	VS->Set();
	PS->Set();

	WB->SetVS(0);
	CB->SetPS(0);

	clips[0]->Render();
}

void AnvilLight::PostRender()
{
}

void AnvilLight::Respawn()
{
	WorldUpdate();

	scale = clips[clip_idx]->GetFrameSize() * size /
		clips[clip_idx]->GetFrameOriginSize();

	is_active = true;
}

void AnvilLight::SetPos(Vector2 pos)
{
	this->pos = pos + offset;
}
