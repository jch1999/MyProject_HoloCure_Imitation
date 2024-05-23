#pragma once
class Environment :public Singleton<Environment>
{
private:
	friend class Singleton;

	Camera* main_camera; // 각각 WVP 변환 중 View 변환 담당

	MatrixBuffer* projection;
	// WVP 변환 중 projection 변환에 사용할 행렬(=상수) 버퍼

	void CreateProjection();	// 위 2개의 변환 행렬을 초기화해줄 함수
	ID3D11SamplerState* samplerState;
	ID3D11BlendState* blendState;
	ID3D11RasterizerState* rasterizerState;

	void CreateSamplerState();
	void CreateBlendState();
	void CreateRasterizerState();

	Environment();
	~Environment();

public:
	Camera* GetMainCamera() { return main_camera; }
};