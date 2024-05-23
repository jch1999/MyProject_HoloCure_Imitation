#pragma once
class PixelShader
// DX의 픽셀 셰이더를 좀 더 편하게 다루기 위해 만든 클래스
{
private:
	ID3D11PixelShader* PS;
	// DX11이 픽셀 셰이더를 다루는 클래스
	static unordered_map<wstring, PixelShader*> shader_data;

public:
	PixelShader(wstring file_loc, 
		DWORD flags = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG);

	static PixelShader* GetInstance(wstring file_loc);
	static void Delete();
	// LPCWSTR = WCHAR = 유니코드를 지원하는 문자 자료형
	// DX에서부터는 기존의 char 문자열을 지원하지 않고 
	// 문자 하나당 2바이트를 이용하는 유니코드 문자열을 이용해야 함
	// 따라서 매개변수 역시 LPCWSTR을 이용해 규격을 맞춰준 것

	// 나중엔 이것 말고 wstring이라는 유니코드 문자열 자료형을 사용할 것
	~PixelShader();

	void Release();
	ID3D11PixelShader* GetPixelShader() { return PS; }
	void Set();
};