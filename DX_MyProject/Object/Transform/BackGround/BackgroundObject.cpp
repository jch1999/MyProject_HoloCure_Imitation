#include "framework.h"

BackgroundObject::BackgroundObject(Vector2 inRenderSize,float inSpawnRate,int inFrameMaxIdx)
	:renderSize(inRenderSize),spawnRate(inSpawnRate), frameMaxIdx(inFrameMaxIdx)
{
	VS = VertexShader::GetInstance(L"Shader/VertexShader/VertexUV.hlsl", 1);
	PS = PixelShader::GetInstance(L"Shader/PixelShader/PixelUV.hlsl");
	CB = new ColourBuffer();
}

BackgroundObject::~BackgroundObject()
{
	delete CB;
}

void BackgroundObject::Render()
{
	if (!is_active)return;
	VS->Set();
	PS->Set();

	WB->SetVS(0);
	CB->SetPS(0);
}

void BackgroundObject::PostRender()
{
}

void BackgroundObject::SetIndex(int inIdx)
{
	frameIdx = inIdx >= frameMaxIdx ? frameMaxIdx-1 : inIdx < 0 ? 0 : inIdx;
	
}

void BackgroundObject::SetMaxIdx(int inIdx)
{
	frameMaxIdx = inIdx;
}

void BackgroundObject::SetTarget(Transform* t)
{
	target = t;
}

void BackgroundObject::SetOffset(Vector2 inOffset)
{
	this->offset = inOffset;
}

void BackgroundObject::SetColor(Float4 inColor)
{
	CB->data.colour = inColor;
}

void BackgroundObject::ChangePos()
{
	pair<int, int> nowPos = make_pair((int)pos.x, (int)pos.y);
	if (activeRecord.find(nowPos) == activeRecord.end())
	{
		float rand = Random::Get()->GetRandomFloat(0.0f, 1.0f);
		if (rand < spawnRate)
		{
			is_active = true;
			SetIndex(Random::Get()->GetRandomInt(0, 1));
			activeRecord[nowPos] = true;
			frameRecord[nowPos] = frameIdx;
		}
		else
		{
			is_active = false;
			activeRecord[nowPos] = false;
		}
	}
	else
	{
		is_active = activeRecord[nowPos];
		SetIndex(frameRecord[nowPos]);
	}
}

void BackgroundObject::InitFrame()
{
}

void BackgroundObject::ClearFrame()
{
}
