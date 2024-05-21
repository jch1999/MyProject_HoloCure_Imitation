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
	// 이 클래스의 인스턴스는 실제 이미지 파일을 로딩해와 저장하는 역할

	LoadFromWICFile(file_loc, WIC_FLAGS_NONE, nullptr, img);
	// 실존하는 파일을 부러와 img에 저장하는 함수
	// 제대로 실행됐으면 img의 값이 변경됨

	CreateShaderResourceView(DEVICE, img.GetImages(), img.GetImageCount(), img.GetMetadata(), &srv);

	// 이미지 설정 여부 반환
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
	// 디바이스 컨텍스트에 사진 데이터가 들어가있는 셰이더 리소스 뷰를 등록

	image->Render();
}
