#include "framework.h"

ScrollImageRect::ScrollImageRect(Vector2 pos, Vector2 size, Vector2 scale, float angle, Matrix* parent)
	:Transform(pos, scale, angle, parent), scroll_speed(Float2(0,0))
{
	image = new ScrollRectUV(size, scroll_speed);
}

ScrollImageRect::~ScrollImageRect()
{
}

bool ScrollImageRect::SetImage(LPCWSTR file_loc)
{
	ScratchImage img;
	// �� Ŭ������ �ν��Ͻ��� ���� �̹��� ������ �ε��ؿ� �����ϴ� ����

	LoadFromWICFile(file_loc, WIC_FLAGS_NONE, nullptr, img);
	// �����ϴ� ������ �η��� img�� �����ϴ� �Լ�
	// ����� ��������� img�� ���� �����

	CreateShaderResourceView(DEVICE, img.GetImages(), img.GetImageCount(), img.GetMetadata(), &srv);

	// �̹��� ���� ���� ��ȯ
	if (srv == nullptr)
		return false;
	else
		return true;
}

void ScrollImageRect::SetScrolling(Float2 scroll_speed)
{
	this->scroll_speed = scroll_speed;
	image->SetScrollSpeed(scroll_speed);
}

void ScrollImageRect::Update()
{
	/*if (scroll_speed.x != 0.0f)
	{
		this->pos.x += scroll_speed.x * DELTA;
	}
	if (scroll_speed.y != 0.0f)
	{
		this->pos.y += scroll_speed.y * DELTA;
	}*/
	image->Update();
	WorldUpdate();
}

void ScrollImageRect::Render()
{
	WB->SetVS(0);
	DVC->PSSetShaderResources(0, 1, &srv);
	// ����̽� ���ؽ�Ʈ�� ���� �����Ͱ� ���ִ� ���̴� ���ҽ� �並 ���

	image->Render();
}
