#include "framework.h"
// �̸� �����ϵ� ����� �ش� ����� �̸� ����ص״ٸ�
// ���� �ڵ� ������ �ڵ� �������� �� �˾Ƽ� �̸� �����ϵ� ����� ���Ե�

unordered_map<wstring, VertexShader*> VertexShader::shader_data;
void VertexShader::CreateInputLayout()
// ������ �츮�� �����ڿ��� Input_Layout�� ������� �κ��� ���� �Լ��� ���� ���̶� ����ϸ� ��
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
    case 0: // ó���� �츮�� �ߴ� �Ϲ����� ����, ��ġ�� ���� ����ϴ� ������ �̿��� ��
        layoutSize = ARRAYSIZE(layouts);
        Device::Get()->GetDevice()->CreateInputLayout(layouts, layoutSize, vertex_blob->GetBufferPointer(),
            vertex_blob->GetBufferSize(), &input_layout);
        break;
    case 1: // ��ġ�� �̹����� ����ϴ� ����
        layoutSize = ARRAYSIZE(layouts_UV);
        Device::Get()->GetDevice()->CreateInputLayout(layouts_UV, layoutSize, vertex_blob->GetBufferPointer(),
            vertex_blob->GetBufferSize(), &input_layout);
        break;
    }
}


void VertexShader::CreateInputLayoutByPos()
// ����ϴ� ������ ��ǥ �ܿ� �ƹ��� �����͵� ������� ���� ��쿡 �̿��ϴ� ���̾ƿ���
// ���� �� �����ϴ� �κ�
// ����� ���⼭ �ݻ�� ���õ� ó������ ��
{
    D3DReflect(vertex_blob->GetBufferPointer(), vertex_blob->GetBufferSize(),
        IID_ID3D11ShaderReflection, (void**)&reflection);
    // �� ���� �ݻ縦 �ٷ�� ��ü�� �ҷ��� reflection�� �����ϴ� �Լ�
    // �ٸ� �츮�� 2D������ ���� �ݻ縦 �ٷ��� ���� ���̱� ������,
    // �츮�� ���� �ٷ� ���� �� �ݿ��� ����

    // Ư�� �̰� �߿��� �� 3D ȯ�濡�� �츮�� ȭ�� ��򰡸� Ŭ������ ��
    // ȭ�鿡�� �� Ŭ���� �κп� �ִ� ������Ʈ�� "���� ���� Ŭ���Ǿ�����"�� �ν��� �� ���Ǵ� ��Ŀ����
    // �� ��(��Ȯ���� ������� ����)�� ��Ҵ��� �ƴ���(=�ݻ簡 �Ͼ���� �ƴ���)��
    // �Ǵ��ؼ� �����ϴ� ��쵵 �ִٺ��ϱ� �������� �ݵ�� ������ �� ������
    // �װ� 2D���� ���� �츮 ���ʹ��� �ƴ� ��

    D3D11_SHADER_DESC shader_desc;
    reflection->GetDesc(&shader_desc);

    // ������ ������ 2D���ٴ� 3D �ʿ��� �� ���� �ٷ�� �� �����̶�,
    // ���⼭�� �԰��� ���߱� ���� �츮�� �� ������ �ұ��ϰ� �Ϻη� ���ߴ� ���� ��
    // ���� �� ������� �ٷ����� ���� ��

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
// ���� �ϳ��� ǥ���ϴµ� 2����Ʈ�� ����ϴ� ���ڿ��� �٤̴� Ŭ����
// �ѱ� ���� �����ڵ带 �ٷ�� �� ���
    :type(type)
{
    //ID3DBlob* vertexBlob;

    D3DCompileFromFile(file_loc.c_str(), nullptr, nullptr, "VS",
        "vs_5_0", flags, 0, &vertex_blob, nullptr);
    // PixelShader�� �Ȱ����� ����(VS), ����(vs_5_0)�� �ٸ�

    DEVICE->CreateVertexShader(vertex_blob->GetBufferPointer(),
        vertex_blob->GetBufferSize(), nullptr, &VS);
    // ������ �Լ��� �ٸ�

    /*
    // Input_layout�� ���̴� ���� ������ �����͸� ���� ��
    // �� �����Ͱ� ��� �����Ǿ��ִ����� �˷��ִ� ���� ������ ��
    // �ٷ� �� ������ ������ ���⿡�� ����
    D3D11_INPUT_ELEMENT_DESC layouts[] =
    {
        {"POSITION", // "���� �� �κ��� ������ �� �ø�ƽ�� �� ���̴�"
        // ��� �������� ����ϴ� �κС�

        0, // �ø�ƽ �ε��� - �ø�ƽ�� �� �̻� ������ ��� ��� �ø�ƽ�� �� �������� ����ϴ� �κ�
        // ���� �ø�ƽ�� �� �̻� ���� �ʱ� ������ �츮�� ������� ����. 0���� ����
        DXGI_FORMAT_R32G32B32_FLOAT,    // �� �κ��� �����ʹ� (����Ʈ������) � ������ �Ǿ��ִ��� ��� ��
        // ���� �� �ƴ϶�(HLSL) �����͸� �˾Ƽ� �ؼ����� ���ϱ� ������,
        // �� �����Ͱ� ������ ������������ ���� �������� �ϴ� ��
        // Red 32bit / Green 32Bit / Blue 32bit�� �Ǽ��� ������ �� 12����Ʈ�� ������

        // �̷� ���� ������ �̰� ���� �� ������, ��� �����͸� �ٷ� �� �ִ� �� �ƴ�
        // �ٸ� ������ �ñ��ϸ� �� ������ ����� ���Ƿ� �� Ȯ���غ� ��

        0,  // ��� "����"�� �� �������� �����ϴ� �κ�
        // �� ���Կ� ���� ���� ��ü�� ���� ������ �����̳�, ��� ������ �ٷ�� �� �����ڿ����� �׻� 0���� ����

        0,  // �� �����Ͱ� ������ ��ü ������ �� ������ ���۵Ǵ���, �� �ε����� ����ϴ� �κ� ��
        // 1��° ���� ���ڰ� �ƴ϶� �������� �ε����� ǥ���ϴ� ���̴� �迭�� ���������� 0���� ����

        D3D11_INPUT_PER_VERTEX_DATA, 0} // �� ���� 2D�� ���� ���ȿ� ���� ���� ���� ����

        ,{"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12,
        D3D11_INPUT_PER_VERTEX_DATA, 0}
        // ����� ���� �ø�ƽ, �ڷ��� ����, �ε���
        // 1) ���� �ٸ� �뵵�� �������̹Ƿ� �� �ٸ� �뵵�� ���Ǵ� �ø�ƽ�� ������ �ٲ��ִ� ��
        // 2) x, y, z 3���� �����͸� �����ϴ� POSITION���� �޸� ������ �����ϴµ��� R,G,B,A 4���� ���� ����ϹǷ�
        // �׿� ���缭 �Ǽ� 4���� �����̶�� �˷��ִ� ������ �ٲ��� �ʿ䰡 ����
        // 3) ù��° �����Ϳ��� POSITION�� �� 12����Ʈ�� �̿�������,
        // �� �κ��� ����ϴ� �����ʹ� 13��° ����Ʈ���� ����
        // �� �ε����� 12�� �Է��� �� �κ��� �����ʹ� 12�� ����Ʈ���� �����Ѵٰ� ���̴��� �˸�
    };

    // uv�� ����ϴ� vertexShader�� layout
    D3D11_INPUT_ELEMENT_DESC layouts_UV[] = {
        {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,
        0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},

        {"UV", 0, DXGI_FORMAT_R32G32_FLOAT,
        0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0}
    };

    UINT layoutSize;
    // �׷��� �԰��� ������ layouts �迭�� �� �뷮�� ���
    // �ٷ� �ؿ� �ִ� CreateInputLayout �Լ����� ���̾ƿ� �迭�� �� �뷮�� ���� ������� ���ϱ� ������,
    // �츮�� �̸� ����ؼ� �˷���� �ϱ� ����
    
    switch (type) // �� ���̴��� ���� ������ �̿��� �������� ���� �ٸ� �۾��� �ϵ��� �ϴ� �κ�
    {
    case 0: // pos + color�� �����ϴ� ������ �̿��ϴ� ���
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
// Singleton�� Get �Լ��� ���� ������ �۾��� �ϴ� �Լ�
{
    if (shader_data.count(file_loc) > 0) // �Էµ� ���ϸ��� ���� ������� ��ü�� �̹� ������ ���
        return shader_data[file_loc];   // �ʿ� �̹� ����Ǿ��ִ� ��ü�� ��ȯ

    VertexShader* instance = new VertexShader(file_loc, type);
    shader_data[file_loc] = instance;   // �ƴ϶�� ���� ������ ��ü�� ���� �ش� Ű�� ����

    return instance;
}

void VertexShader::Delete()
{
    // ���̴����� ����� ���� �����ٸ� ��� ���̴����� �Ҵ� ������ �� ����� �Լ�����,
    // �׷� ��Ȳ�̸� �ƿ� ���α׷� ��ü�� ����Ǵ� ��Ȳ�̹Ƿ� ���� ó���� ������ ����
    // ���� ���⼱ �ۼ����� ����, ������ �ۼ��ϴ� ���� ����ȴٰ� ����
    for (auto shader : shader_data)
    {
        delete shader.second;
    }
}