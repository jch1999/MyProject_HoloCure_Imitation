#include "framework.h"
shared_ptr<const Frame> ItemLight::itemLightFrame;
int ItemLight::itemLightUseCnt = 0;

ItemLight::ItemLight(Vector2 pos)
	:size(Vector2(55.0f,105.0f)*1.5f)
{
	VS = VertexShader::GetInstance(L"Shader/VertexShader/VertexUV.hlsl", 1);
	PS = PixelShader::GetInstance(L"Shader/PixelShader/PixelUV.hlsl");
	CB = new ColourBuffer();

	this->pos = pos + offset;

	if (!itemLightFrame)
	{
		InitFrame();
	}

	frame = itemLightFrame;;

	CB->data.colour = Float4(1.0f, 1.0f, 1.0f, 0.85f);
	is_active = false;

	++itemLightUseCnt;
}

ItemLight::~ItemLight()
{
	delete CB;

	if ((--itemLightUseCnt) == 0)
	{
		ClearFrame();
	}
}

void ItemLight::Update()
{
	if (!is_active)return;
	WorldUpdate();

	scale = frame->GetFrameSize() * size /
		frame->GetFrameOriginSize();
}

void ItemLight::Render()
{
	if (!is_active)return;
	
	VS->Set();
	PS->Set();

	WB->SetVS(0);
	CB->SetPS(0);

	frame->Render();
}

void ItemLight::PostRender()
{
}

void ItemLight::Respawn()
{
	WorldUpdate();

	scale = frame->GetFrameSize() * size /
		frame->GetFrameOriginSize();

	is_active = true;
}

void ItemLight::InitFrame()
{
	if (itemLightFrame) return;
	
	wstring file = L"Textures/Item/PC Computer - HoloCure - Save the Fans - Pickups_rm_bg.png";

	frame = make_shared<const Frame>(file, 205.0f, 144.0f, 55.0f, 105.0f);
}

void ItemLight::ClearFrame()
{
	if (!itemLightFrame) return;

	itemLightFrame.reset();
}

void ItemLight::SetPos(Vector2 pos)
{
	this->pos = pos + offset;
}
