#pragma once

class VertexShader
{
private:
	ID3D11VertexShader* VS;
	// ���� ���̴��� ����� Ŭ���� ��ü
	ID3D11InputLayout* input_layout;
	// DirectX ��ġ�� � ���� �����͸� ������ ������
	// �� ���̾ƿ�(=����)�� ������ �����صδ� ��ü
	// ���⿡ ����� �����͸� ���� ������ �ԷµǾ��� �� ���̴� ������ �̸� �ؼ��Ͽ� �̿�
	 
	ID3DBlob* vertex_blob; // �����ڿ��� ����ߴ�, ���̴� ������ �ʿ��� �ӽ� ��ü�� �ɹ��� ���� ��
	ID3D11ShaderReflection* reflection;	// ���� �ݻ� ����, ������ �ǹ��� �ݻ縦 �����ϴ� �� �ʿ��� �ɹ�
	// ��, �츮�� ���� �� ���� ������, ������ �ڵ��� ȣȯ�� ������ �ۼ��� �Ϳ� �Ұ�

	static unordered_map<wstring, VertexShader*> shader_data;
	// ���� ������ �̿��� ���� ���̴���,
	// ������ �̸��� Ű�� ��Ƽ� ������ �ʿ����� ���� map�� ������
	// �� ��, ���� ������ �̸��� ���� VertexShader�� ��ü�� ȣ��ȴٸ�
	// ���⿡ �ֳ� üũ�Ͽ� ������ �� �ڸ����� ����, ������ �ش� ��ü�� ��ȯ

	void CreateInputLayout();
	void CreateInputLayoutByPos();
	UINT type;

public:
	VertexShader(wstring file_loc, UINT type = 0,
		DWORD flags = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG);
	~VertexShader();

	static VertexShader* GetInstance(wstring file_loc, UINT type = 0);
	static void Delete();
	// Singleton�� ���� ��, �ܺο��� �����ڸ� ��ٷ� ȣ���� �� ������
	// ������ ������ ���ϴ� �ν��Ͻ� �����ڸ� ������� ���� ��ﳯ ��
	// ���� �� ����� Ŭ������ Singleton�� �ƴ�.
	// ������, ��ü�� �ҷ��� �� new�� �׳� ���� �� �ƴ϶� �� �Լ��� �̿��ϴ� ������
	// �̹� ������� ��ü�� ���� ��� �߰��� ������ �ʰ� �������� ���� ����
	// �̸� ���� static���� �ڷᱸ���� ����������,
	// ���������� static���� �ش� �ڷᱸ���� �Ҵ� �����ϱ� ���� delete �Լ��� ������ ��

	void Release();
	ID3D11InputLayout* GetInputLayout() { return input_layout; }
	ID3D11VertexShader* GetVertexShader() { return VS; }

	void Set();
};