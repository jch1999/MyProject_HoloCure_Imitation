#include "framework.h"
#include "NewCircle_ver_Instructor.h"

NewCircle_ver_Instructor::NewCircle_ver_Instructor(Float2 p, Float2 s, float a,
    Float2 size, float dir, D3D11_PRIMITIVE_TOPOLOGY t)
    : Transform(p, s, a), dir(dir)
{
    circle = new SRTCircle_ver_Instructor(size, 30, t);
}

NewCircle_ver_Instructor::NewCircle_ver_Instructor(Float2 p, Float2 s, float a,
    float radius, float dir, D3D11_PRIMITIVE_TOPOLOGY t)
    : NewCircle_ver_Instructor(p, s, a, Float2(radius, radius), dir, t)
{
}

NewCircle_ver_Instructor::~NewCircle_ver_Instructor()
{
    delete circle;
}

void NewCircle_ver_Instructor::Update(Matrix* parent)
{
    rot.z += dir;
    // 말 그대로 Z축 기준의 회전각을 매 Update 함수가 호출될 때마다 0.001씩 증가시키라는 의미
    // 그리고 이 Update 함수는 Scene의 Update 함수가 호출될 때,
    // 다시말해 Program.Update()가 호출될 떄마다 이 코드가 실행되는 것

    // 그에 따라 이 함수는 정해진(사실은 호출될 떄마다의) 주기에 따라
    // 이 트랜스폼의 회전각을 계속해서 움직이는 것이다

    if (this->parent != parent)
        SetParent(parent);

    WorldUpdate();
    // WorldTransform의 parent에 다른 오브젝트의 World를 입력한 것임을 알 수 있음
    // 이번에도 F12로 해당 함수의 정의로 이동
}

void NewCircle_ver_Instructor::Render()
{
    WB->SetVS(0);
    circle->Render();
}