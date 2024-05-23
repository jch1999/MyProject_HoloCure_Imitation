#pragma once
class PixelShader
// DX�� �ȼ� ���̴��� �� �� ���ϰ� �ٷ�� ���� ���� Ŭ����
{
private:
	ID3D11PixelShader* PS;
	// DX11�� �ȼ� ���̴��� �ٷ�� Ŭ����
	static unordered_map<wstring, PixelShader*> shader_data;

public:
	PixelShader(wstring file_loc, 
		DWORD flags = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG);

	static PixelShader* GetInstance(wstring file_loc);
	static void Delete();
	// LPCWSTR = WCHAR = �����ڵ带 �����ϴ� ���� �ڷ���
	// DX�������ʹ� ������ char ���ڿ��� �������� �ʰ� 
	// ���� �ϳ��� 2����Ʈ�� �̿��ϴ� �����ڵ� ���ڿ��� �̿��ؾ� ��
	// ���� �Ű����� ���� LPCWSTR�� �̿��� �԰��� ������ ��

	// ���߿� �̰� ���� wstring�̶�� �����ڵ� ���ڿ� �ڷ����� ����� ��
	~PixelShader();

	void Release();
	ID3D11PixelShader* GetPixelShader() { return PS; }
	void Set();
};