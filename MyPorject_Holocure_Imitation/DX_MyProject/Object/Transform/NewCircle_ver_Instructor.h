#pragma once
class NewCircle_ver_Instructor : public Transform
{
private:
    SRTCircle_ver_Instructor* circle;
    float dir;
    // 원의 회전방향(인 동시에 회전속도)를 이 멤버 변수로 관리

public:
    NewCircle_ver_Instructor(Float2 p, Float2 s, float a, Float2 size, float dir,
        D3D11_PRIMITIVE_TOPOLOGY t = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    NewCircle_ver_Instructor(Float2 p, Float2 s, float a, float radius, float dir,
        D3D11_PRIMITIVE_TOPOLOGY t = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    ~NewCircle_ver_Instructor();

    void Update(Matrix* parent = NULL);
    void Render();

    void SetColor(Float4 colour)
    {
        circle->SetColor(colour);
    }

};