#include "framework.h"

void CircleCollider::CreateLine()
{
    float angle = (M_PI * 2);
    for (UINT i = 0; i <= vertex_count; i++)
    {
        verticies.emplace_back(cos(angle) * radius, sin(angle) * radius);
        angle -= 2 * (float)(M_PI) / vertex_count;
    }

    VB = new VertexBuffer(verticies.data(), sizeof(VertexPos), verticies.size());
}

bool CircleCollider::isAABB(RectCollider* collider)
// 회전하지 않은 사각형 충돌판정과 충돌여부를 검사하는 함수
{
    Vector2 half = collider->Size() * 0.5f;
    Vector2 closest; // 원과 사각형 사이에서 제일 가까운 거리 - ? 사각형에서 원의 중심에 제일 가까운 점의 위치

    if (pos.x < collider->pos.x - half.x) // 원의 중심점이 상자의 왼쪽 끝보다 더 왼쪽일 경우
        closest.x = collider->pos.x - half.x;
    else if (pos.x > collider->pos.x + half.x) // 원의 중심점이 상자의 오른쪽 끝보다 더 오른쪽일 경우
        closest.x = collider->pos.x + half.x;
    else
        closest.x = pos.x;

    // 위의 내용을 Y좌표에 대해서도 실행
    if (pos.y < collider->pos.y - half.y) // 원의 중심점이 상자의 위쪽 끝보다 더 위쪽일 경우
        closest.y = collider->pos.y - half.y;
    else if (pos.y > collider->pos.y + half.y) // 원의 중심점이 상자의 아래쪽 끝보다 더 아래쪽일 경우
        closest.y = collider->pos.y + half.y;
    else
        closest.y = pos.y;

    // 그렇게 구한 사각형에서 원과 제일 가까운 점이 
    // 먼저 원 안에 존재하는지를 검사

    if (isPointCollision(closest))
        return true;
    else
    // 원은 특정한 점에서 같은 거리에 있는 점들을 모은 것
    // 그 점들보다 가까운 거리에 있으면 원 안에 들어간 것

    // 지금 우리가 위에서 구한 것은 "사각형에서 제일 가까운 점"을 구하는 것
    // = 이 점이 아닌 사각형 안에 점은 모조리 이 점보다 원과의 거리가 멀다
    // 따라서 이 점이 원 안에 들어가있지 않다면 당연히 다른 점들 역시 원 안에 들어가지 않을 것
    // 반대로 말하면, 그 제일 가까운 점이 원 안에 들어가있다면 그 사각형은 원과 겹치는 부분이 있다
        return false;
}

bool CircleCollider::isOBB(RectCollider* collider)
// 일단 편의상 OBB라는 이름으로 만들기는 했으나
// 실제로는 지금 여기서 사용되는 알고리즘을 OBB라고 부르지는 않음
{
    Matrix T = XMMatrixTranslation(pos.x - collider->pos.x, pos.y - collider->pos.y, 0.0f);
    // 두 원을 기점으로 하려 새로운 T 행렬을 만들어야 함
    // 정확히는 나 자산(원형 충돌경계)의 중심울 기준으로 하여 사각형의 중심점이 어디에 있는지를 계산하고,
    // 그렇게 구한 상대거리를 원점으로 삼는 새로운 월드를 만들어야 함

    Matrix circle_world = S * R * T;
    // S와 R은 이 원이 가진 Transform에서 월드 업데이트할 때 썼던 값을 그대로 이용하고,
    // T 행렬만 위의 행렬로 교체하면 중앙점(=원점)을 사각형의 중심점으로 이동
    circle_world *= XMMatrixRotationZ(-collider->rot.z);
    // 그렇게 구한 새로운 월드 행렬에 사각형이 회전해 있는 만큼을 반대방향으로 회전시킴

    // 이 작업을 통해 "사각형이 회전하지 않았다고 가정했을 때"의 사각형과 원의 위치를 임시로 구현
    
    XMFLOAT4X4 temp_matrix;
    XMStoreFloat4x4(&temp_matrix, circle_world);
    // 위에서 구한 행렬을 사용하기 편하게 Float4X4 행렬에 복사,
    Vector2 circle_obb_center = Vector2(temp_matrix._41, temp_matrix._42);
    // 그렇게 복사되어 이용하기 편해진 행렬에서 position 값만을 추출

    // 이하의 내용은 약간의 수정을 거쳐서 여기서도 사용하는 AABB 알고리즘
    // 그냥 원 자체의 pos ㄱ밧을 썼던 것에서 위의 circle_obb_center로 교체

    Vector2 half = collider->Size() * 0.5f;
    Vector2 closest; // 원과 사각형 사이에서 제일 가까운 거리 - ? 사각형에서 원의 중심에 제일 가까운 점의 위치

    // 지금 이 부분의 조건식은 원의 중심이 아닌 삭가형의 중심에서 판독하고 있으므로
    // 사각형의 중심 좌표를 구하는 부부이 들어갈 필요가 없음 collider->pos 부분 삭제
    if (circle_obb_center.x < - half.x) // 원의 중심점이 상자의 왼쪽 끝보다 더 왼쪽일 경우
        closest.x = - half.x;
    else if (circle_obb_center.x > half.x) // 원의 중심점이 상자의 오른쪽 끝보다 더 오른쪽일 경우
        closest.x =  half.x;
    else
        closest.x = circle_obb_center.x;

    // 위의 내용을 Y좌표에 대해서도 실행
    if (circle_obb_center.y < - half.y) // 원의 중심점이 상자의 위쪽 끝보다 더 위쪽일 경우
        closest.y = - half.y;
    else if (circle_obb_center.y > half.y) // 원의 중심점이 상자의 아래쪽 끝보다 더 아래쪽일 경우
        closest.y = half.y;
    else
        closest.y = circle_obb_center.y;

    // 이 부부은 AABB와는 살짝 다르게,
    // 제일 가까운 점이 원의 중심가지의 거리가 어떻게 되는지를 계산한 뒤,
    // 그게 원의 반지름보다 짧으면 원에 충돌한 것
    // 아니면 충돌하지 않은 것

    if ((circle_obb_center-closest).GetLength()<GetRadius())
        return true;
    else
        return false;

    // 이 알고리즘의 핵심 아이디어
    // 사각형이 회전했다?
    // 그러면 사각형을 중점으로 해서 사각형이 회전하지 않았다 가정할 경우의 원의 위치를 구한 뒤
    // 기존의 원을 중심으로 했던 코드에서 사각형을 중심으로 하는 코드로서 살짝 변형한 AABB 코드를 이용
}

CircleCollider::CircleCollider(float rad)
    :radius(rad)
{
    type = TYPE::CIRCLE;
    vertex_count = 50;
    CreateLine();
}

CircleCollider::~CircleCollider()
{
    delete VB;
}

/*
* 원 - 하나의 점에서 정해진 거리만큼 떨어진 점들의 집합
* -> 어떤 점이 원 안에 들어와있는지를 판단하는 것은 그 점과 원의 중심 사이의 거리가 원의 반지름보다 작은 지로 판단
* 원과 원의 충돌의 경우엔 같은 논리로 두 원을 구성하는 점들 중
* 하나라도 다른 원의 안에 들어가있는지 판단하는 식인데,
* 다르게 말하면 모든 점이 서로의 밖에 있을 수 밖에 없는 상황인지 아닌지를 검사하는 것으로
* 충돌 여부를 판단하는 것
*/
bool CircleCollider::isPointCollision(Vector2 point)
{
    Vector2 dir = pos - point;

    if (dir.GetLength() < radius)
        return true;
    else
        return false;
}

bool CircleCollider::isCircleCollision(CircleCollider* collider)
{
    Vector2 dir = pos - collider->pos;

    if (dir.GetLength() < radius + collider->GetRadius())
        return true;
    else
        return false;
}

bool CircleCollider::isRectCollision(RectCollider* collider, Vector2* overwrap)
{
    return isOBB(collider);
    // 사각형과 달리 원의 충돌에선 AABB 충돌을 쓸 이유가 그리 많지 않기 때문에 OB를 쓴다고 기억해둬도 됨
    // 다만 둘 다 시도해보긴 할 것
}

bool CircleCollider::isLineCollision(Vector2 line_start, Vector2 line_end)
{
    return false;
}
