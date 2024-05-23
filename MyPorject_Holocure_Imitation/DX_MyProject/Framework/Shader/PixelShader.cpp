#include "framework.h"

unordered_map<wstring, PixelShader*> PixelShader::shader_data;

PixelShader::PixelShader(wstring file_loc, DWORD flags)
{
    ID3DBlob* pixelBlob;
    // 셰이더를 만들기 위해 잠깐 사용하는 버퍼(=임시 저장소)\

    D3DCompileFromFile(file_loc.c_str()/*L"Shader/VertexShader.hlsl"*/, nullptr, nullptr, "PS",
        "ps_5_0", flags, 0, &pixelBlob, nullptr);
    // 파일주소를 입력받아, 거기에 위의 버퍼 등을 이용해 픽셀 셰이더 객체를 동적 할당하고 초기화하는 함수
    // 다른 맴버들은 우리가 쓸 일이 없으니 무시해도 되고, 이 맴버들만 기억하면 됨
    
    // file_loc = 이름 그대로 우리가 로드할 셰이더 파일의 주소를 의미
    // 경로 자체에 대해서는 다음주에 프로젝트 세팅법을 설명하면서 같이 설명
    // nullptr이나 &pixelBlob 등은 무시하고
    // "PS" = 이 셰이더가 어떤 셰이더인지를 표기하는 역할, 여기서는 픽셀 셰이더를 만드니 PS
    // "ps_5_0" = 이 셰이더의 버전 -> 이 셰이더가 사용하는 정점이 어느 버전을 사용하는지를 명시하는 코드
    // 이게 프로젝트 설정과 일치하지 않을 경우 에러가 발생할 소지가 잇음
    // flags = 셰이더를 생성할 때 설정을 세팅하는 변수
    // 우리가 이 값을 바꿀 필요는 없지만, 이 함수가 반드시 요구하는 내용이기 때문에 기억해둘 필요가 있음

    DEVICE->CreatePixelShader(pixelBlob->GetBufferPointer(),
        pixelBlob->GetBufferSize(), nullptr, &PS);
    // 셰이더의 생성에 성공했다면, 이를 Device에 설정하여 우리가 사용할 수 있는 형태로 동적 할당을 완성

    pixelBlob->Release();
    // 용도가 끝난 버퍼는 할당 해제
}

PixelShader::~PixelShader()
{
	Release();
}

PixelShader* PixelShader::GetInstance(wstring file_loc)
{
    if (shader_data.count(file_loc) > 0) // 입력된 파일명을 통해 만들어진 객체가 이미 존재할 경우
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
    // 이 코드를 그대로 이용해 VertexShader::Delete() 역시 만들어도 무방
}

void PixelShader::Release()
{
	PS->Release();
    // 해당 클래스에서 할당 해제를 지원해주고 있으니 이를 호출
}

void PixelShader::Set()
{
    DVC->PSSetShader(PS, nullptr, 0);
}
