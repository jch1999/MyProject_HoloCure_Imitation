#include "framework.h"
// 미리 컴파일된 헤더에 해당 헤더를 미리 등록해뒀다면
// 이후 코드 파일을 자동 생성했을 때 알아서 미리 컴파일된 헤더가 포함됨

unordered_map<wstring, VertexShader*> VertexShader::shader_data;
void VertexShader::CreateInputLayout()
// 기존에 우리가 생성자에서 Input_Layout을 만들었던 부분을 따로 함수로 빼온 것이라 기억하면 됨
{
    D3D11_INPUT_ELEMENT_DESC layouts[] =
    {
        {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,
        0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0}
        ,{"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12,
        D3D11_INPUT_PER_VERTEX_DATA, 0}
    };

    D3D11_INPUT_ELEMENT_DESC layouts_UV[] =
    {
        {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,
        0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
        {"UV", 0, DXGI_FORMAT_R32G32_FLOAT,
        0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0}
    };

    UINT layoutSize;
    switch (type)
    {
    case 0: // 처음에 우리가 했던 일반적인 정점, 위치와 색을 사용하는 정점을 이용할 떄
        layoutSize = ARRAYSIZE(layouts);
        Device::Get()->GetDevice()->CreateInputLayout(layouts, layoutSize, vertex_blob->GetBufferPointer(),
            vertex_blob->GetBufferSize(), &input_layout);
        break;
    case 1: // 위치와 이미지를 사용하는 정점
        layoutSize = ARRAYSIZE(layouts_UV);
        Device::Get()->GetDevice()->CreateInputLayout(layouts_UV, layoutSize, vertex_blob->GetBufferPointer(),
            vertex_blob->GetBufferSize(), &input_layout);
        break;
    }
}


void VertexShader::CreateInputLayoutByPos()
// 사용하는 정점이 좌표 외에 아무런 데이터도 사용하지 않을 경우에 이용하는 레이아웃을
// 선언 및 적용하는 부분
// 겸사겸사 여기서 반사와 관련되 처리까지 함
{
    D3DReflect(vertex_blob->GetBufferPointer(), vertex_blob->GetBufferSize(),
        IID_ID3D11ShaderReflection, (void**)&reflection);
    // 빛 등의 반사를 다루는 객체를 불러와 reflection에 저장하는 함수
    // 다만 우리는 2D에서는 빛의 반사를 다루지 않을 것이기 때문에,
    // 우리가 직접 다룰 일은 이 반에선 없음

    // 특히 이게 중요한 건 3D 환경에서 우리가 화면 어딘가를 클릭했을 때
    // 화면에서 그 클릭한 부분에 있는 오브젝트가 "내가 지금 클릭되었구나"를 인식할 때 사용되는 매커니즘에
    // 이 빛(정확히는 뻗어나가는 직선)이 닿았는지 아닌지(=반사가 일어났는지 아닌지)를
    // 판단해서 판정하는 경우도 있다보니까 언젠가는 반드시 익혀야 할 개념임
    // 그게 2D만을 배우는 우리 기초반은 아닐 뿐

    D3D11_SHADER_DESC shader_desc;
    reflection->GetDesc(&shader_desc);

    // 이하의 내용은 2D보다는 3D 쪽에서 더 자주 다루게 될 내용이라,
    // 여기서는 규격을 맞추기 위해 우리가 안 씀에도 불구하고 일부러 맞추는 것일 뿐
    // 직접 이 내용들을 다루지는 않을 것

    vector<D3D11_INPUT_ELEMENT_DESC> input_layouts;

    for (UINT i = 0; i < shader_desc.InputParameters; i++)
    {
        D3D11_SIGNATURE_PARAMETER_DESC paramDesc;
        reflection->GetInputParameterDesc(i, &paramDesc);

        D3D11_INPUT_ELEMENT_DESC elementDesc;
        elementDesc.SemanticName = paramDesc.SemanticName;
        elementDesc.SemanticIndex = paramDesc.SemanticIndex;
        elementDesc.InputSlot = 0;
        elementDesc.AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
        elementDesc.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
        elementDesc.InstanceDataStepRate = 0;

        if (paramDesc.Mask == 1)
        {
            if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32)
                elementDesc.Format = DXGI_FORMAT_R32_UINT;
            else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32)
                elementDesc.Format = DXGI_FORMAT_R32_SINT;
            else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32)
                elementDesc.Format = DXGI_FORMAT_R32_FLOAT;
        }
        else if (paramDesc.Mask < 4)
        {
            if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32)
                elementDesc.Format = DXGI_FORMAT_R32G32_UINT;
            else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32)
                elementDesc.Format = DXGI_FORMAT_R32G32_SINT;
            else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32)
                elementDesc.Format = DXGI_FORMAT_R32G32_FLOAT;
        }
        else if (paramDesc.Mask < 8)
        {
            if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32)
                elementDesc.Format = DXGI_FORMAT_R32G32B32_UINT;
            else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32)
                elementDesc.Format = DXGI_FORMAT_R32G32B32_SINT;
            else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32)
                elementDesc.Format = DXGI_FORMAT_R32G32B32_FLOAT;
        }
        else if (paramDesc.Mask < 16)
        {
            if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32)
                elementDesc.Format = DXGI_FORMAT_R32G32B32A32_UINT;
            else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32)
                elementDesc.Format = DXGI_FORMAT_R32G32B32A32_SINT;
            else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32)
                elementDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
        }

        string temp = paramDesc.SemanticName;
        if (temp == "POSITION")
            elementDesc.Format = DXGI_FORMAT_R32G32B32_FLOAT;

        input_layouts.push_back(elementDesc);
    }

    DEVICE->CreateInputLayout(input_layouts.data(), input_layouts.size(),
        vertex_blob->GetBufferPointer(), vertex_blob->GetBufferSize(), &input_layout);
}


VertexShader::VertexShader(wstring file_loc, UINT type, DWORD flags)
// 문자 하나를 표기하는데 2바이트를 사용하는 문자열을 다ㅜ는 클래스
// 한글 등의 유니코드를 다루는 데 사용
    :type(type)
{
    //ID3DBlob* vertexBlob;

    D3DCompileFromFile(file_loc.c_str(), nullptr, nullptr, "VS",
        "vs_5_0", flags, 0, &vertex_blob, nullptr);
    // PixelShader와 똑같지만 종류(VS), 버전(vs_5_0)만 다름

    DEVICE->CreateVertexShader(vertex_blob->GetBufferPointer(),
        vertex_blob->GetBufferSize(), nullptr, &VS);
    // 이쪽은 함수명만 다름

    /*
    // Input_layout은 셰이더 측에 정점의 데이터를 보낼 때
    // 그 데이터가 어떻게 구성되어있는지를 알려주는 명세서 역할을 함
    // 바로 그 명세서의 내용을 여기에서 설정
    D3D11_INPUT_ELEMENT_DESC layouts[] =
    {
        {"POSITION", // "지금 이 부분의 정보는 이 시멘틱에 들어갈 것이다"
        // 라고 도착지를 명시하는 부분★

        0, // 시멘틱 인덱스 - 시멘틱이 둘 이상 존재할 경우 어느 시멘틱에 들어갈 것인지를 명시하는 부분
        // 같은 시멘틱을 둘 이상 쓰지 않기 때문에 우리는 사용하지 않음. 0으로 고정
        DXGI_FORMAT_R32G32B32_FLOAT,    // 이 부분의 데이터는 (바이트상으로) 어떤 구조로 되어있는지 명시 ★
        // 같은 언어가 아니라서(HLSL) 데이터를 알아서 해석하지 못하기 때문에,
        // 이 데이터가 어디부터 어디까지인지를 직접 명시해줘야 하는 것
        // Red 32bit / Green 32Bit / Blue 32bit의 실수로 구성된 총 12바이트의 데이터

        // 이런 식의 포멧은 이것 말고도 더 있으나, 모든 데이터를 다룰 수 있는 건 아님
        // 다른 포멧이 궁금하면 위 열거형 상수의 정의로 들어가 확인해볼 것

        0,  // 어느 "슬롯"에 들어갈 것인지를 결정하는 부분
        // 이 슬롯에 대한 개념 자체는 후일 설명할 예정이나, 적어도 정점을 다루는 이 생성자에서는 항상 0으로 고정

        0,  // 이 데이터가 정점의 전체 데이터 중 어디부터 시작되는지, 그 인덱스를 명시하는 부분 ★
        // 1번째 등의 숫자가 아니라 데이터의 인덱스를 표기하는 것이니 배열과 마찬가지로 0부터 시작

        D3D11_INPUT_PER_VERTEX_DATA, 0} // 이 둘은 2D를 배우는 동안에 사용될 일이 없는 변수

        ,{"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12,
        D3D11_INPUT_PER_VERTEX_DATA, 0}
        // 변경된 것은 시멘틱, 자료의 구성, 인덱스
        // 1) 서로 다른 용도의 데이터이므로 그 다른 용도로 사용되는 시멘틱에 들어가도록 바꿔주는 것
        // 2) x, y, z 3개의 데이터를 관리하는 POSITION과는 달리 색상을 지정하는데는 R,G,B,A 4개의 값을 사용하므로
        // 그에 맞춰서 실수 4개의 구성이라고 알려주는 것으로 바꿔줄 필요가 있음
        // 3) 첫번째 데이터였던 POSITION이 총 12바이트를 이용했으니,
        // 이 부분이 담당하는 데이터는 13번째 바이트부터 시작
        // 그 인덱스인 12를 입력해 이 부분의 데이터는 12번 바이트부터 시작한다고 셰이더에 알림
    };

    // uv를 사용하는 vertexShader용 layout
    D3D11_INPUT_ELEMENT_DESC layouts_UV[] = {
        {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,
        0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},

        {"UV", 0, DXGI_FORMAT_R32G32_FLOAT,
        0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0}
    };

    UINT layoutSize;
    // 그렇게 규격을 지정한 layouts 배열의 총 용량을 계산
    // 바로 밑에 있는 CreateInputLayout 함수에서 레이아웃 배열의 총 용량을 직접 계산하지 못하기 때문에,
    // 우리가 미리 계산해서 알려줘야 하기 때문
    
    switch (type) // 이 셰이더가 무슨 정점을 이용할 것인지에 따라 다른 작업을 하도록 하는 부분
    {
    case 0: // pos + color를 지정하는 정점을 이용하는 경우
        layoutSize = ARRAYSIZE(layouts);
        DEVICE->CreateInputLayout(layouts, layoutSize, vertex_blob->GetBufferPointer(),
            vertex_blob->GetBufferSize(), &input_layout);
        vertex_blob->Release();
        break;
    case 1:
        layoutSize = ARRAYSIZE(layouts_UV);
        DEVICE->CreateInputLayout(layouts_UV, layoutSize, vertex_blob->GetBufferPointer(),
            vertex_blob->GetBufferSize(), &input_layout);
        vertex_blob->Release();
        break;
    default:
        break;
    }
    */
    if (type == 2)
        CreateInputLayoutByPos();
    else
        CreateInputLayout();

}

VertexShader::~VertexShader()
{
    Release();
}

void VertexShader::Release()
{
    VS->Release();
    input_layout->Release();
}

void VertexShader::Set()
{
    DVC->IASetInputLayout(input_layout);
    DVC->VSSetShader(VS, nullptr, 0);
}

VertexShader* VertexShader::GetInstance(wstring file_loc, UINT type)
// Singleton의 Get 함수와 거의 동일한 작업을 하는 함수
{
    if (shader_data.count(file_loc) > 0) // 입력된 파일명을 통해 만들어진 객체가 이미 존재할 경우
        return shader_data[file_loc];   // 맵에 이미 저장되어있는 객체를 반환

    VertexShader* instance = new VertexShader(file_loc, type);
    shader_data[file_loc] = instance;   // 아니라면 새로 생성한 객체를 맵의 해당 키에 저장

    return instance;
}

void VertexShader::Delete()
{
    // 셰이더들의 사용이 전부 끝났다면 모든 셰이더들을 할당 해제할 때 사용할 함수지만,
    // 그럴 상황이면 아예 프로그램 자체가 종료되는 상황이므로 굳이 처리할 이유가 없음
    // 따라서 여기선 작성하지 않음, 본래는 작성하는 것이 권장된다고만 정리
    for (auto shader : shader_data)
    {
        delete shader.second;
    }
}