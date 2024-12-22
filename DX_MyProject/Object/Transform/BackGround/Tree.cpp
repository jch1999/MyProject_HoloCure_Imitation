#include "framework.h"

vector<shared_ptr<const Frame>> Tree::treeFrames;
int Tree::TreeUseCnt = 0;

Tree::Tree()
	:spawnRate(0.85f)
{
	VS = VertexShader::GetInstance(L"Shader/VertexShader/VertexUV.hlsl", 1);
	PS = PixelShader::GetInstance(L"Shader/PixelShader/PixelUV.hlsl");
	CB = new ColourBuffer();

	if (treeFrames.empty())
	{
		InitFrame();
	}

	collider = new RectCollider(Vector2(48.0f, 30.0f));

	ChangePos();
	
	++TreeUseCnt;
}

Tree::~Tree()
{
	delete collider;
	delete CB;

	if ((--TreeUseCnt) == 0)
	{
		ClearFrame();
	}
}

void Tree::Update()
{
	if (!is_active)return;

	scale = frame->GetFrameSize() * renderSize / frame->GetFrameOriginSize();
	Vector2 before_pos = pos;
	pos = target->pos + offset;
	WorldUpdate();

	collider->pos = pos + colliderOffset;
	collider->WorldUpdate();

	if ((before_pos - pos).GetLength() > 1.0f)
	{
		ChangePos();
	}
}

void Tree::Render()
{
	if (!is_active)return;
	VS->Set();
	PS->Set();

	WB->SetVS(0);
	CB->SetPS(0);
	frame->Render();
	collider->Render();
}

void Tree::PostRender()
{
}

void Tree::InitFrame()
{
	if (!(treeFrames.empty())) return;

	wstring file = L"Textures/Background/PC Computer - HoloCure - Save the Fans - Stage 1 - Grassy Plains_rm_bg.png";

	// leaf tree
	treeFrames.emplace_back(make_shared<const Frame>(file, 4.0f, 151.0f, 137.0f, 133.0f));
	// leaf less tree
	treeFrames.emplace_back(make_shared<const Frame>(file, 141.0f, 151.0f, 116.0f, 127.0f));
}

void Tree::ClearFrame()
{
	if (treeFrames.empty()) return;

	treeFrames.clear();
}

void Tree::SetIndex(int idx)
{
	switch (idx)
	{
	case 0:
		frame = treeFrames[idx];
		renderSize = Vector2(137.0f, 133.0f) * 1.5f;
		colliderOffset = Vector2(5.0f, 60.0f);
		break;
	case 1:
		frame = treeFrames[idx];
		renderSize = Vector2(116.0f, 127.0f) * 1.5f;
		colliderOffset = Vector2(5.0f, 60.0f);
		break;
	default:
		break;
	}
}

void Tree::ChangePos()
{
	pair<int, int> now_pos = make_pair((int)pos.x, (int)pos.y);
	if (activeRecord.find(now_pos)==activeRecord.end())
	{
		float rand = Random::Get()->GetRandomFloat(0.0f, 1.0f);
		if (rand < spawnRate)
		{
			is_active = true;
			SetIndex(Random::Get()->GetRandomInt(0, 1));
			collider->SetActive(true);
			activeRecord[now_pos] = true;
			frameRecord[now_pos] = frameIdx;
		}
		else
		{
			is_active = false;
			collider->SetActive(false);
			activeRecord[now_pos] = false;
		}
	}
	else
	{
		is_active = activeRecord[now_pos];
		collider->SetActive(is_active);
		SetIndex(frameRecord[now_pos]);
	}
}
