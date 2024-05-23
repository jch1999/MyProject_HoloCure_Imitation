#include "framework.h"

Device* Device::instance = nullptr;

UINT width = WIN_WIDTH;
UINT height = WIN_HEIGHT;

Device::Device()
{
	CreateDeviceAndSwapChain();
	CreateBackBuffer();
	SetViewPoint();
}

Device::~Device()
{
	device->Release();
	device_context->Release();

	swap_chain->Release();
	render_target_view->Release();
}

void Device::CreateDeviceAndSwapChain()
// 더블버퍼링 관련 설정을 초기화하는 함수
// 그 동시에 Device 자체도 초기화함
{
    DXGI_SWAP_CHAIN_DESC sd = {};
    // 백버퍼 관련 설정을 저장해둘 인스턴스
    // 이렇게 선언해둔 뒤 아래의 내용들을 입력하여 백버퍼를 동적 할당할 때 사용

    sd.BufferCount = 1; 

    sd.BufferDesc.Width = width;
    sd.BufferDesc.Height = height;
    // 백버퍼가 다룰 화면의 크기

    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    // 백버퍼가 다룰 그래픽이 사용하는 색상의 규격
    // R8G8B8A8 = 적색 8비트, 녹색 8비트, 청색 8비트, 알파값 8비트를 이용하는 32비트 그래픽

    sd.BufferDesc.RefreshRate.Numerator = 60;
    sd.BufferDesc.RefreshRate.Denominator = 1;
    // FPS와 연관된 설정이라고만 기억하면 OK
    // 2D에서는 이걸 이용해 FPS를 관리하지 않을 것이므로 상세하게 다룰 일이 없음

    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    // 이 버퍼가 어디에 사용될 것인지 결정

    sd.OutputWindow = hWnd;
    // 이 백버퍼가 그림을 출력할 창이 무엇인지 정의하는 부분

    // 이 hWnd만큼은 외부에서 받아와서 사용해야 함
    // 그 때문에 이를 extern 전역 변수로 선언하고
    // 메인 파일에서 이를 초기화하는 것

    sd.SampleDesc.Count = 1;
    sd.SampleDesc.Quality = 0;
    // 3D 쪽에서 사용하는 기능이라 우리는 안 씀

    sd.Windowed = true;
    // 창이 전체화면인지 창모드인지를 결정하는 맴버

    D3D11CreateDeviceAndSwapChain(
        nullptr,
        D3D_DRIVER_TYPE_HARDWARE,
        0,
        D3D11_CREATE_DEVICE_DEBUG,
        nullptr,
        0,
        D3D11_SDK_VERSION,
        &sd,
        &swap_chain,
        &device,
        nullptr,
        &device_context
    );
    // 그렇게 설정된 sd를 이용해서 더블버퍼링 스왑체인, DX를 활용하기 위한 device와 device_context를 
    // 한번에 초기화
    
    // 기존의 더블버퍼링을 설정하는 부분을 그대로 가져옴
}

void Device::CreateBackBuffer()
// 백버퍼를 초기화하고 디바이스에 등록하는 함수
{
    ID3D11Texture2D* backBuffer = nullptr;

    swap_chain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backBuffer);
    device->CreateRenderTargetView(backBuffer, nullptr, &render_target_view);
    // 스왑체인과 디바이스 각각에서 백버퍼를 설정해주는 함수

    backBuffer->Release();

    device_context->OMSetRenderTargets(1, &render_target_view, nullptr);
    // 설정된 백버퍼를 실제로 그림 기르는 걸 총괄하는 device_context에 등록

    // API 쪽에서는 우리가 직접 백버퍼를 이런저런 매개변수를 동원하여 교체해줘야 했으나,
    // DX에서는 처음 실행할 때만 이거저거 설정해주고
    // 나중에 백버퍼를 교체할 때는 간단한 함수 하나만 호출해주는 것으로 끝낼 수 있음

    // 지난 프로젝트에서 백버퍼를 설정하고 디바이스에 이를 등록하는 부분을 가져옴
}

void Device::SetViewPoint()
// 뷰포트를 설정하는 부분
{
    // 2D 보다는  3D에서 더 자주 사용할 내용이기 때문에
    // 여기서는 그냥 이런 게 있다 정도로만 기억하면 됨

    D3D11_VIEWPORT viewPort;
    viewPort.Width = width; // 우리가 설정한 창의 크기 전체를 화면에 표시하겠다
    viewPort.Height = height; // 마찬가지
    viewPort.MinDepth = 0.0f; // 깊이를 따지는 내용
    viewPort.MaxDepth = 1.0f; // 이에 대해서는 추후 3D를 배울 떄 다루게 될 것
    viewPort.TopLeftX = 0.0f;
    viewPort.TopLeftY = 0.0f;
    device_context->RSSetViewports(1, &viewPort);

    // 기존에 뷰포트를 세팅할 때 사용했던 코드를 그대로 가져와 사용

}

void Device::Clear()
// 화면을 초기화하는 함수
{
    float clear_color[4] = { 0.0f, 0.125f, 0.3f, 1.0f };
    // 배경색을 지정

    device_context->ClearRenderTargetView(render_target_view, clear_color);
    // 지정된 배경색으로 화면의 모든 내용을 지우라고 device_context에 요청
}

void Device::Present()
// 더블버퍼링을 실행하는 함수 -> 실제로 화면을 출력하는 함수
{
    swap_chain->Present(0, 0);
    // 스왑체인에 화면을 바꾸라고 요청하는 함수를 호출함으로서 백버퍼와 현제 화면을 교체
}
