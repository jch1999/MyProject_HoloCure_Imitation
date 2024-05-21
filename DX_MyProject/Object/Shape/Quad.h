#pragma once
// Quad : 일반적으로 "넷"을 뜻하는 말이지만,
// 여기서는 사각형이라 보면 됨
// -> 사각형의 "이미지"를 출력하기 위한 클래스

// 기존의 Shape는 SRT 변환을 통한 위치 관리를 직접 할 수 없는 클래스였으므로,
// 이를 스스로 관리할 수 잇게 Transform을 상속시킨 새 클래스가 필요했음
// -> 그래서 출력 부분을 포함해서 전부 관리할 수 잇는 새 클래스를 지금 만드는 것
class Quad : public Transform
{

protected:
    vector<VertexUV> vertices = {};
    vector<UINT> indices = {}; // 정점을 사용할 순서가 기록된 버퍼

    VertexShader* VS;
    PixelShader* PS;

    VertexBuffer* VB;
    IndexBuffer* IB;
    // 인덱스(순서) 버퍼 : 어는 순서대로 정점을 사용할 것인지 결정하는 버퍼

    ColourBuffer* CB;
    MatrixBuffer* WB;

    Texture* texture;
    // 이미지 파일을 담당하는 인스턴스
    // 이미지 파일 같은 것을 한 프로그램 내에서 두 번 이상 부를 경우 최적화 문제가 생기기 마련이니
    // 이를 해결하고자 만든 클래스

    void SetPixelShader(wstring file);
    // 우리가 도형을 출력할 때 사용하는 셰이더를 바꾸는 상황이 있을 수 있음
    // 그럴 때 가른 셰이더를 이용하겠다고 설정해주는 함수

public:
    Quad(wstring file, Vector2 scale = Vector2(1, 1),
        Vector2 startUV = Vector2(0, 0), Vector2 EndUV = Vector2(1, 1));
    virtual ~Quad();

    Vector2 Size() { return texture->GetSize() * scale; }
     void Render();

private:
    void Create();

};