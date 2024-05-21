#include "framework.h"

ScrollingBG::ScrollingBG(Vector2 pos, Vector2 size, Vector2 scale, float angle, Matrix* parent)
	:Transform(pos, scale, angle, parent),size(size)
{
	/*
	* 원래 진행하려던 것
	* 2개의 이미지를 서로 다른 인스턴스로서 생성,
	* 처음 위치는 하나의 이미지는 화면 중앙, 다른 하나의 이미지는 화면 오른쪽 바깥에 위치하도록 설정
	* 그 뒤 시간경과에 따라 오른쪽에서 왼쪽으로 이동시키고
	* 첫번째 이미지가 완전히 화면 밖으로 나갔으면 그 이미지만을 오른쪽으로 옮겨서
	* 다시 중앙에 있는 이미지가 밖으로 나가는 만큼 화면 오른쪽에서 이미지를 돌려오는 식으로 하려 했음
	* 
	* 그러나 RectUV는 Transform이 아닌, 좌표 관련해가지는 정점의 위치밖에 없음
	* 따라서 이 RectUV의 좌표를 이동시키고자 한다면,
	* 정점 자체의 좌표를 고치는 수 밖에 없었다
	* 
	* 하지만 그 방식은 오브젝트(=트랜스폼) 자체의 좌표가 변경될 경우
	* 우리가 의도하지 않았던 좌표 이동이 발생할 수 있으며,
	* 원상복귀를 할 수 있게 만드는 난이도가 확 높아짐
	* 따라서 Shape 측의 정점 자체의 정보는 어지간하면 건드리지 않고 싶다
	* 
	* 그렇게 할 경우 사실상 하나의 오브젝트(=Transform)에서는 이미지의 좌표를 하나밖에 지정하지 못하는 셈
	* 따라서, 하나의 오브젝트에서 둘 이상의 이미지를 출력시키고자 한다면 
	* Transform을 이용하지 않는 Shape 클래스만을 상속시킨 클래스가 아니라
	* 추가로 Transform 역시 상속박은 출력 전용 클래스를 만들어서 이용하는 것이 더 나음
	* 
	* 이에 해당하는 클래스인 Quad를 지금부터 만들 것
	*/

	image[0] = new Quad(L"Textures/Images/parallax-forest-layer-merge.png", Vector2(1, 1),
		Vector2(-1, 0), Vector2(2, 1));
	image[1] = new Quad(L"Textures/Images/parallax-forest-layer-merge.png", Vector2(1, 1),
		Vector2(-1, 0), Vector2(2, 1));
	// UV 값을 지정하는 것으로 이미지를 몇번 표기할 것인지 등을 결정
	// 자세한 건 저번에도 했듯 CreateSampleState에 설명되어 있음

	/* Quad에서 진행되도록 변경
	ScratchImage img;
	// 이 클래스의 인스턴스는 실제 이미지 파일을 로딩해와 저장하는 역할

	LoadFromWICFile(L"Textures/Images/parallax-forest-layer-merge.png", WIC_FLAGS_NONE, nullptr, img);
	// 실존하는 파일을 부러와 img에 저장하는 함수
	// 제대로 실행됐으면 img의 값이 변경됨

	CreateShaderResourceView(DEVICE, img.GetImages(), img.GetImageCount(), img.GetMetadata(), &srv);
	// metaData 이미지의 크기 같은 정보들이 담겨 있는 데이터
	// 맴버 변수 src에 DEVICE와 img를 이용해 "셰이더 리소스 뷰"라는 것을 생성,
	// 이걸 통해서 셰이더에 사진 데이터를 보냄
	// PixelUV.hlsl 쪽에서 다루는 samp와 map 등을 다루기 위해 필요한 내용
	*/

	image[0]->pos = pos;
	image[0]->scale = size / image[0]->Size();
	// 우리는 이 오브젝트를 배경화면으로서 쓰고자 하는 것이므로, 하나의 이미지는 기본적으로 화면을 꽉 채워야 함
	// 그러나 각 이미지의 scale이 1이라면 당연히 원래 이미지의 사이즈만큼만 출력되고 끝이므로,
	// 전체 화면에 맞게 출력하려면 그에 걸맞는 스케일 설정이 필요한 것
	// 이를 입력받은 사이즈(화면 전체 사이즈) / 사용하고자 하는 이미지의 크기

	image[1]->pos = pos + Vector2(size.x, 0);
	image[1]->scale = size / image[1]->Size();

	for (Quad* q : image)
	{
		q->is_active = true;
	}
}

ScrollingBG::~ScrollingBG()
{
	for (auto i : image)
		delete i;
	//srv->Release();
}

void ScrollingBG::Update()
{
	speed = float(size.x) / 5.0f * DELTA;

	for (Quad* q : image)
	{
		q->pos.x -= speed;
		if (q->pos.x <= -size.x / 2.0f) // 현재 스크린이 화면을 완전히 나간 순간
			// = 이미지 전체 크기의 절반만큼의 거리만틈 이 이미지의 중심이 화면의 왼쪽으로 나간 순간
			q->pos.x += size.x * 2.0f;
	}

	for (Quad* q : image)
	{

		q->WorldUpdate();
	}

	// 사실 지금 상황에선 각각의 화면의 위치를 조정하는 것과
	// 그렇게 업데이트된 데이터들을 월드 행렬에 반영시키는 것과 궅이 다른 순서로 실행될 필요가 없음
	// 그러나 다른 모든 배경의 위치를 업데이트 끝낸 뒤에 
	// 최종적으로 월드 행렬에 반영시켜야 하는 경우가 있다보니
	// -> 각 이미지의 위치가 두 번 이상에 걸쳐서 결정되어야 하는 경우 등
	// 이런 경우를 대비해 일단은 분리시켜 둔 것

	// 이렇게 Quad를 통해서 스크롤링을 구현해보니
	// 정점 자체의 데이터를 바꾸지 않고도 스크롤하는 것을 구현할 수 있었고,
	// 스크롤되는 형식이 약간 맘에 안 드는 것을 그 자리에서 수치 살짝 조정해주는 것으로
	// 간단히 자연스럽게 만들 수 있었음
	// + 나중에 스클롤 방향 등을 바꾸고자 할 경우, 혹은 회전까지 시켜야 할 경우는
	// 그냥 이 이미지들의 pos, rot 등을 이용하면 간단히 해결할 수 있음

	// 그래서 하나의 오브젝트가 여러 이미지를 이용해야 하는 경우는 Quad를 이용하면 더 쉽게 구축할 수 있음
	// (대신 이 Quad를 구축하는데 시간이 더 많이 걸리기는 했지만, 쉽게 이용하기 위한 공사비로 여깁시다)
}

void ScrollingBG::Render()
{
	WB->SetVS(0);
	//DVC->PSSetShaderResources(0, 1, &srv);
	// 디바이스 컨텍스트에 사진 데이터가 들어가있는 셰이더 리소스 뷰를 등록

	image[0]->Render();
	image[1]->Render();
}
