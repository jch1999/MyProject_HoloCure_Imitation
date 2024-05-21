#include "framework.h"

Environment::Environment()
{
	CreateProjection();
	// WVP 변환 중 View, Porjection 변환을 담당할 변환 행렬들을 이 시점에서 초기화

	CreateSamplerState();
	CreateBlendState();
	CreateRasterizerState();
	// 외부 텍스쳐 파일의 인식 및 출력을 위해 설정해야 하는 state들을 여기서 초기화

	main_camera = new Camera();
	// 카메라를 초기화하면서 V 변환을 담당할 뷰 변활 행렬 역시 초기화
}

Environment::~Environment()
{
	delete main_camera;
	delete projection;
}

// 이하의 내용들은 기존의 Program에서 그대로 가져온 것으로
// 앞으로는 이 Environment, 환경이라는 이름에 걸맞게
// 기본적인 세팅들은 환경을 전담하는 이 클래스에서 설정해둘 것

void Environment::CreateSamplerState()
// 입력받은 이미지를 어떻게 처리할 것인지를 결정하는 state
// state : 상태라는 뜻이므로 그냥 설정이라 이해하면  OK

// 자세한 설명은 실제로 그림을 출력해보고 설명
{
	D3D11_SAMPLER_DESC desc = {};
	desc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
	// 이 이미지를 어떤 식으로 "보간"할 것인지 지정하는 부분
	// 보간 : 인접한 데이터들 사이에 있는, 데이터가 아직 정해지지 않은 점에
	// 적합한 함수를 이용해 들어갈 데이터를 만들어주는 행위

	// 간단히 말하면 이미지의 크기가 변했을 때 좀 더 자연스럽게 출력되도록 하는 보정
	// 그 보간을 어떤 식으로 할 것인지 결정하는 게 이 멤버
	// 주로 2D에서는 위에서 쓴 MIN_MAG_MIP_POINT라는 상수 보간을 이용하고,
	// 3D에서는 MIN_POINT_MIG_MAP_LINEAR라는 선형 보간을 사용하는 경우가 많음

	desc.AddressU = D3D11_TEXTURE_ADDRESS_MIRROR;
	desc.AddressV = D3D11_TEXTURE_ADDRESS_MIRROR;
	desc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	// 입력받은 이미지 파일을 실제 좌표에 위치시킬 때,
	// uv값이 0과 1 사이의 범위를 벗어나는 경우가 있음
	// 그럴 때, 0과 1 사이의 범위를 벗어난 부분에는 어떤 식으로 출력하는 내용을 
	// 그 방식을 정하는 부분
	// 여기서 이미지의 좌우는 U, 상하는 V의 값을 바꿨을 때 적용되는 것을 보면 감이 잡히겠지만,
	// 위에 있는 U,V,W는 각각 실제 Transform의 X, Y, Z에 대응함
	// 즉 U는 가로에서의 그림 처리방식, V는 세로에서의 그림 처리방식을 결정

	// MIRROR : 1의 단위를 넘을 때마다 직전 영역에 있던 내용을 반전시켜서 출력하는 모드
	// BORDER : 0~1까지의 범위만 정상적으로 출력, 그 범위 밖은 프로그램 자체의 배경색으로 채움
	// WRAP : 0~1까지의 범위 바깥은 같은 이미지를 반복해서 채운다
	// CLAMP : 글로 설명하긴는 어려움, 0~1까지의 범위 밖은 이미지 경계의 픽셀값을 가져다 사용한다.
	//			마지막 부분을 쭉 늘려서 사용하는 느낌?
	//			0~1까지의 범위 제일 끝부분을 결정하는 픽셀 부분으로 그 바깥 부분을 전부 채움
	//	같은 X좌표(V) or Y좌표(U)에 있는 픽셀은 전부 같은 색으로 채우는 방식
	// MIRROR_ONCE : -1 ~1까지의 범위는 MIRROR, 그 외의 범위는 CLAMP로 처리하는 방식

	desc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	desc.MinLOD = 0;
	desc.MaxLOD = D3D11_FLOAT32_MAX;
	// 이 부분들은 3D에서는 다루기도 하나 2D에서는 다루지 않음
	// 따라서 이 셋은 설명을 생략

	DEVICE->CreateSamplerState(&desc, &samplerState);

	DVC->PSSetSamplers(0, 1, &samplerState);

}

void Environment::CreateBlendState()
// 지금까지 DX에서 색상을 다룰 때 언급했던 "알파값"을 이용해서 투명처리를 하는 부분
// 알파값 : 해당 픽셀이 가진 색상 데이터의 "불투명도"를 의미하는 값
// 1이면 완벽한 불투명(=무언가 색을 가지고 있어서 이를 출력해야 한다),
// 0이면 완벽한 투명(=실제로는 데이터상 무슨 색을 가지고 있다 하더라도 없는 것으로 취급한다)
// 이를 이용해서 입력받은 이미지, 혹은 정점의 색상이 우리가 "투명으로 취급할 값"과 동일하다면
// 해당 데이터는 출력하지 않도록 하는 영역

// ...이론상으로는 이렇긴 한데
// 실질적으로는 DX에서는 말 그대로 알파값이 0일 때가 아니면 투명으로서 처리하지 못하기 때문에
// 우리가 사용할 이미지에서 투명처리할 부분을 추가로 처리해야 할 필요가 있음
// 따라서 여기서는 그냥 투명 처리를 위해 이 함수를 구성해줘야 한다고만 기억하면 됨

/*
* 그래픽 프로그래밍에서 색을 투명으로 처리하는 방법은 크게 2가지
*
* 1) 위에서 설명한 알파값이 0인 경우를 투명색으로 처리하는 방식
* 지금 이 프로젝트에서는 이 방법을 채택하고 있음
*
* 2) 특정한 한 가지 색이 입력됐을 경우 그 색을 무시하도록 설정하는 방식
* 흔히 말하는 "크로마키"가 이 방식을 이용해 투명처리를 하는 방법
* 영화 등에서 CG작업으로 촬영할 때 뒤에 그린 스크린 같은 걸 두는 것이 이 방식으로 투명을 처리하는 것
*
* 어지간한 그래픽 툴에서는 위 2번째 방법을 이용하는 경우가 대부분
* 그런데, DirectX에선 이 2번째 방법은 제대로 지원하지 않고 첫번째 방법만을 지원하고 있음
* 따라서 이미지의 배경 등을 투명처리하여 이미지 파일 안에 있는 캐릭터만 처리하고자 한다면
* 우리가 직접 이미지 파일의 배경을 투명색으로 바꿔줘야만 함 - 외부 그래픽 툴을 이용해서 그림파일 자체를 편집해야 함
*/
{
	D3D11_BLEND_DESC desc = {};
	desc.RenderTarget[0].BlendEnable = true;
	desc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	desc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;

	desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_INV_SRC_ALPHA;
	desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;

	desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	DEVICE->CreateBlendState(&desc, &blendState);

	float blendFactor[] = { 0, 0, 0, 0 };
	DVC->OMSetBlendState(blendState, blendFactor, 0xffffffff);
}

void Environment::CreateRasterizerState()
// 그래픽 파이프라인에서 설명했던 Resterizer 셰이더 단계를 처리하는 부분
// 2D보단 3D에서 더 자주 쓰이는 구간이므로 자세한 설명은 생략
{
	D3D11_RASTERIZER_DESC desc = {};
	desc.CullMode = D3D11_CULL_NONE;
	desc.FillMode = D3D11_FILL_SOLID;

	DEVICE->CreateRasterizerState(&desc, &rasterizerState);

	DVC->RSSetState(rasterizerState);
}

void Environment::CreateProjection()
// WVP 변환에 사용할 행렬 중 투영(projection) 행렬을 설정하는 함수
// 원래는 View 행렬은 본 함수가 아닌 다른 곳에서 초기화해야 하는 내용이지만,
// 아직은 우리가 view를 따로 다루지 않기 때문에 후일 Camera를 도입하기 전까진는 여기서 다룸
{
	projection = new MatrixBuffer();
	// 변환에 사용할 행렬들을 정의

	Matrix orthographic = XMMatrixOrthographicOffCenterLH
	(
		0.0f, (float)WIN_WIDTH, // 화면의 가로 왼쪽 끝의 x좌표와 오른쪽 끝의 x좌표를 정의
		(float)WIN_HEIGHT, 0.0f, // 같은 식으로 화면의 아래쪽 끝과 위쪽 끝의 y좌표를 정의
		// 위(x좌표)와는 순서가 정반대로 큰쪽에서 작은 쪽으로 가는데,
		// 이는 WinAPI와 규격을 통일하기 위한 조치,
		// 이렇게 설정하지 않으면 당장에 API를 통해 마우스의 위치를 받을 때 상하가 반전되어버림
		-1.0f, 1.0f	// Z좌표를 다루는 부분으로, 2D에서는 딱히 사용하지 않으므로 디폴트값인 -1.0 ~ 1.0으로 설정
	);
	// 우리가 사용할 3D 공간을 화면에 표기할 때,
	// 그 표기하는 범위가 어디부터 어디까지인지 설정하는 행렬
	// 좀 더 정확히는 우리가 사용할 "좌표계"를 정의하는 행렬

	// -> 그리고 이는 동시에 실제 공간에 있는 내용물 중
	// 화면에 표시할 것을 어디부터 어디까지로 지정할 것인지를 명확히 정의하기도 함

	// => 여기에 들어가있는 값이 변하더라도
	// 실제로 공간상에 존재하는 물질 등의 위치 같은 정보는 전혀 바뀌지 않는다
	// 이를 이용하면, 즉 orthographic의 값을 바궈서 등록하는 기능을 만들어준다면
	// 줌인/줌아웃을 구현할 수 있다

	projection->Set(orthographic); // 그렇게 만들어진, 앞으로 투영을 담당할 행렬을 버퍼에 세팅(=값 복사)

	projection->SetVS(2); // 여기를 SetPS로 잘못해놓고 있었네..
	// 세팅이 완료된 변환 행렬을 정점 셰이더의 1, 2번 슬롯으로 보내기
	// 이렇게 하여 WVP 변환 중 P 변환의 준비물이 완성
}