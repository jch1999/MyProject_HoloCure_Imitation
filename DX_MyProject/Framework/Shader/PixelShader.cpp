#include "framework.h"

unordered_map<wstring, PixelShader*> PixelShader::shader_data;

PixelShader::PixelShader(wstring file_loc, DWORD flags)
{
    ID3DBlob* pixelBlob;
    // ���̴��� ����� ���� ��� ����ϴ� ����(=�ӽ� �����)\

    D3DCompileFromFile(file_loc.c_str()/*L"Shader/VertexShader.hlsl"*/, nullptr, nullptr, "PS",
        "ps_5_0", flags, 0, &pixelBlob, nullptr);
    // �����ּҸ� �Է¹޾�, �ű⿡ ���� ���� ���� �̿��� �ȼ� ���̴� ��ü�� ���� �Ҵ��ϰ� �ʱ�ȭ�ϴ� �Լ�
    // �ٸ� �ɹ����� �츮�� �� ���� ������ �����ص� �ǰ�, �� �ɹ��鸸 ����ϸ� ��
    
    // file_loc = �̸� �״�� �츮�� �ε��� ���̴� ������ �ּҸ� �ǹ�
    // ��� ��ü�� ���ؼ��� �����ֿ� ������Ʈ ���ù��� �����ϸ鼭 ���� ����
    // nullptr�̳� &pixelBlob ���� �����ϰ�
    // "PS" = �� ���̴��� � ���̴������� ǥ���ϴ� ����, ���⼭�� �ȼ� ���̴��� ����� PS
    // "ps_5_0" = �� ���̴��� ���� -> �� ���̴��� ����ϴ� ������ ��� ������ ����ϴ����� ����ϴ� �ڵ�
    // �̰� ������Ʈ ������ ��ġ���� ���� ��� ������ �߻��� ������ ����
    // flags = ���̴��� ������ �� ������ �����ϴ� ����
    // �츮�� �� ���� �ٲ� �ʿ�� ������, �� �Լ��� �ݵ�� �䱸�ϴ� �����̱� ������ ����ص� �ʿ䰡 ����

    DEVICE->CreatePixelShader(pixelBlob->GetBufferPointer(),
        pixelBlob->GetBufferSize(), nullptr, &PS);
    // ���̴��� ������ �����ߴٸ�, �̸� Device�� �����Ͽ� �츮�� ����� �� �ִ� ���·� ���� �Ҵ��� �ϼ�

    pixelBlob->Release();
    // �뵵�� ���� ���۴� �Ҵ� ����
}

PixelShader::~PixelShader()
{
	Release();
}

PixelShader* PixelShader::GetInstance(wstring file_loc)
{
    if (shader_data.count(file_loc) > 0) // �Էµ� ���ϸ��� ���� ������� ��ü�� �̹� ������ ���
        return shader_data[file_loc];

    PixelShader* instance = new PixelShader(file_loc);
    shader_data[file_loc] = instance;

    return instance;
}

void PixelShader::Delete()
{
    for (auto shader : shader_data)
    {
        delete shader.second;
    }
    // �� �ڵ带 �״�� �̿��� VertexShader::Delete() ���� ���� ����
}

void PixelShader::Release()
{
	PS->Release();
    // �ش� Ŭ�������� �Ҵ� ������ �������ְ� ������ �̸� ȣ��
}

void PixelShader::Set()
{
    DVC->PSSetShader(PS, nullptr, 0);
}
