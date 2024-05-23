#pragma once

class Device
// DirectX 환경을 제대로 실행하기 위해서 필요한 기능들을 관리하는 클래스
// 이 클래스를 통해서 DirectX와 관련된 객체들을 초기화하고, 관련된 작업들을 실행
{
private:
	ID3D11Device* device;    // CPU의 연산, 리소스 로딩 등 출력 외 다른 기능들을 종합적으로 하는 기본 장치
	ID3D11DeviceContext* device_context; // GPU에서 하는 일을 여기서 담당

	IDXGISwapChain* swap_chain;  // 더블버퍼링에 사용되는 객체
	ID3D11RenderTargetView* render_target_view;   // 후면버퍼에서 사용할 메모리

	static Device* instance;

	Device();
	~Device();

public:
	static Device* Get()
	{
		if (instance == nullptr)
			instance = new Device();

		return instance;
	}

	static void Delete() { delete instance; }

	void CreateDeviceAndSwapChain();
	void CreateBackBuffer();
	void SetViewPoint();

	void Clear();
	void Present();

	ID3D11Device* GetDevice() { return device; }
	ID3D11DeviceContext* GetDeviceContext() { return device_context; }
};