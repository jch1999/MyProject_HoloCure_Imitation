#pragma once
class Collider : public Transform
// 그래픽 프로그램이에서 오브젝트와 오브젝트가 충돌했는지 판단할 때는
// 각 오브젝트마다 "충돌범위"를 지정두고
// 그 두 오브젝트의 충돌범위를 특정 알고리즘을 통해 비교해서
// 그 알고리즘을 통과했는지 걸렸는지 판정하는 식으로 충돌여부를 검사함

// 문제는 그 충돌했을 때 사용하는 알고리즘이라는 것이 상당히 복잡한 탓에,
// 실제로 사용되는 알고리즘만 하더라도 다양함
// 우리는 알고리즘을 사용하지 않는 무식한 방법 1가지와 알고리즘 2가지를 사용해 볼 것

// 클래스 자체의 완성은 다음 시간에 할 것이며,
// 이번엔 일단 헤더만 구성 및 설명
{
public:
    enum class TYPE
    {
        RECT,
        CIRCLE
    };
    // 2D 환경에서 주로 사용되는 충돌 판정은 사각형 판정과 원형 판정 2종류가 있음
    // 이 2종류 각가이 사용하는 충돌 구현방식이 다르기 때문에, 서로 다른 자식 클래스로서 만들 예정

protected:
    TYPE type; // 부모 클래스를 호출할 때 자식 클래스가 들어온 상황이면 이게 무슨 클래스인지 모르니
    // 위에 선언했던 열거형 클래스의 맴버로 어떤 클래스인지를 기록해두는 것

    VertexShader* VS;
    PixelShader* PS;

    VertexBuffer* VB;

    ColourBuffer* CB;
    MatrixBuffer* WB;

    vector<VertexPos> verticies;

    // 자기자신의 경계선을 표시하기 위한 용도로서 출력에 필요한 맴버들을 지금 이렇게 선언해둔 것
    // 다만, 좌표 외에 다른 데이터는 일절 필요없기 대문에 좌표 데이터만 가진 정점을 이용해야 함
    // 충돌 판정 범위를 화면에 출력하기 위한 부분


    static bool debug_mode;

public:
    Collider();
    virtual ~Collider();

    void Render();
    TYPE GetType() { return type; }

    static void SetDebugMode() { debug_mode = !debug_mode; }

    virtual bool isCollision(Collider* collider, Vector2* overwrap = NULL);
    // 입력받은 충돌판정이 어떤 타입이냐에 따라 아래에 있는 다른 함수를 호출하는 중개 함수

    // 이 아래의 함수들은 전부 "특정한 대상과 충돌했는지"를 검사하는 함수

    virtual bool isPointCollision(Vector2 point) = 0;
    virtual bool isCircleCollision(class CircleCollider* collider) = 0;
    virtual bool isRectCollision(class RectCollider* collider,
        Vector2* overwrap = NULL) = 0;
    virtual bool isLineCollision(Vector2 line_start, Vector2 line_end) = 0;

    static bool isLineCrossCollision(Vector2 l1_start, Vector2 l1_end,
        Vector2 l2_start, Vector2 l2_end);

    void SetColor(float r, float g, float b)
    {
        CB->data.colour = Float4(r, g, b, 1);
    }

protected:
    virtual void CreateLine() = 0;

};

/*
* 과제 : 위에서도 이야기했듯, 충돌 여부를 검사하는 알고리즘은 한 두 가지가 아님
* 
* 그 중에서 우리는 AABB와 OBB라고 하는 2가지 알고리즘을 주로 만들어볼 것인데,
* 이 둘이 각각 어떤 알고리즘인지 조사해오기
*/