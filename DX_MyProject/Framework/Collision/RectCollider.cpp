#include "framework.h"
#include "RectCollider.h"

bool RectCollider::isPointCollision(Vector2 point)
// 이 사각형 충돌판정 안에 입력받은 점이 들어와있는지를 검사하는 함수
{
    // AABB와 OBB보다 훨씬 간단한 방법?
    Vector2 half = Size() * 0.5f;

    float left = GlobalPos().x - half.x;
    float right = GlobalPos().x + half.x;
    float top = GlobalPos().y - half.y;
    float bottom = GlobalPos().y + half.y;
    // 위의 연산을 통해 이 사각형의 범위를 계산

    // 그렇게 연산된 범위 안에 입력된 좌표가 들어있는지를 판단
    if (point.x > left && point.x < right)
    {
        if (point.y > top && point.y < bottom)
            return true; // 들어와있다면 충돌한 것
    }
    return false; // 아니라면 충돌하지 않은 것
}

bool RectCollider::isCircleCollision(CircleCollider* collider)
{
    return isOBB(collider);
}

bool RectCollider::isRectCollision(RectCollider* collider, Vector2* overwrap)
{
    /* 저번에도 이야기했지만 충돌여부를 판정하는 알고리즘의 종류는 상당히 많음
    그 중에서 우리가 조사해왔던 알고리즘은 AABB와 OBB 2가지였는데,
    이런 알고리즘을 이용하지 않고 만들어보고자 한다면 이런 식으로 만들 수 있다는 것도 알아두고가기 위해
    
    맨 처음엔 이 2가지가 아닌 다른 알고리즘을 이용해 충돌여부를 처리하는 것을 시도해봄*/
    /* 이 방식은 아이디어 자체는 매우 간단하며, 회전한 점의 좌표만 구할 수 있다면
    회전에도 대응하는 충돌방식이기는 함

    그러나 무조건 꼭지점 8개를 점검하기 때문에 필연적으로 속도가 느려질 수 밖에 없고,
    무엇보다 한 사각형이 다른 사각형을 뚫는 형태의 상황에서는 충돌했다고 인식하지 못하기 때문에
    실제로는 사용할 수 없는 알고리즘

    더 중요한 건, 관련 알고리즘 등을 배우지 않은 상황에서는 쉽게 떠올릴 수 있을 법한 알고리즘이란 것
    다른 알고리즘을 차용하지 않고 믿바갇에서부터 새로이 구성할 경우엔 제대로 동작하는지 장담하기 힘듦
    이 때문에 이미 성능이 검증된 다른 알고리즘을 배워서 이용하는 것

    Vector2 half = Size() * 0.5f;

    float left = GlobalPos().x - half.x;
    float right = GlobalPos().x + half.x;
    float top = GlobalPos().y - half.y;
    float bottom = GlobalPos().y + half.y;
    // 나 자신의 좌표들을 구하는 과정

    half = collider->Size() * 0.5f;

    float desc_left = collider->GlobalPos().x - half.x;
    float desc_right = collider->GlobalPos().x + half.x;
    float desc_top = collider->GlobalPos().y - half.y;
    float desc_bottom = collider->GlobalPos().y + half.y;
    // 상대방의 좌표들을 구하는 과정

    // 이렇게 하면 양쪽 사각판정의 꼭지점들의 위치를 지정할 수 있음
    // 나의 왼쪽과 위, 상대방의 오른쪽과 아래 같은 식
    // 그렇게 해서 얻을 수 있는 총 8개의 꼭지점을
    // 상대방 측 클래스의 점충돌 함수를 호출하여 서로의 꼬지점이 상대방의 안에 들어가 있는지를 체크하는 식으로 충돌여부를 검사할 수 있음

    if (collider->isPointCollision(Vector2(left, top))
        || collider->isPointCollision(Vector2(left, bottom))
        || collider->isPointCollision(Vector2(right, top))
        || collider->isPointCollision(Vector2(right, bottom))
        || isPointCollision(Vector2(desc_left, desc_top))
        || isPointCollision(Vector2(desc_left, desc_bottom))
        || isPointCollision(Vector2(desc_right, desc_top))
        || isPointCollision(Vector2(desc_right, desc_bottom))
        )
        return true;
    else
        return false;
    */

    // 실제로는 상황에 따라 AABB나 OBB 알고리즘 등을 이용하는 것
    // 지금은 둘 다 완성되진 않은 상황이라 AABB만 여기서 호출하는 식으로 이용할 것이나
    // 나중에는 AABB와 OBB 중 무엇을 사용할 것인지 매개변수를 통해 확정하는 식으로 구성할 것

    if (overwrap != NULL)
        return isAABB(collider, overwrap);
    else
        return isOBB(collider);
}

bool RectCollider::isLineCollision(Vector2 line_start, Vector2 line_end)
{
    return false;
}

void RectCollider::CreateLine()
{
    Vector2 half = size * 0.5f;

    // linestrip이므로 시계 방향, 시계 반대 방향 상관이 없다고 함
    verticies.emplace_back(-half.x, +half.y);
    verticies.emplace_back(+half.x, +half.y);
    verticies.emplace_back(+half.x, -half.y);
    verticies.emplace_back(-half.x, -half.y);
    verticies.emplace_back(-half.x, +half.y);

    VB = new VertexBuffer(verticies.data(), sizeof(VertexPos), verticies.size());
}

bool RectCollider::isAABB(RectCollider* rect, Vector2* overwrap)
// Axis - Aligned Bounding Box의 줄임말
// 축이 나란한 경계상자 -> 충돌판정을 이루는 모든 상자의 변들이 기본 축과 평행하도록 만들어진 경우
// 사용하는 알고리즘
// 기본적으로 매우 빠르다는 것이 장점
// 그러나, (지금의 구조로는) 회전하지 않은 경우에만 정상적으로 동작한다는 것이 제일 큰 단점
{
    float min_right = min(RightVX(), rect->RightVX());
    // 2개의 사각형 충돌판정을 비교해,
    // 둘 중 어느 쪽의 오른쪽 변이 X축에 기준으로 더 왼쪽에 있는지 계산

    float max_left = max(LeftVX(), rect->LeftVX());
    // 같은 식으로둘 중 어느 사각형의 왼쪽 변이 더 오른쪽에 있는지 계산

    // 위 내용을 Y축에도 똑같이 시행해 위쪽 변과 아래쪽 변을 구함
    float min_down = min(DownVX(), rect->DownVX());
    float max_up = max(UpVX(), rect->UpVX());

    // 이렇게 구한 4개의 값을 통해, 사각형을 하나 정의할 수 있게 됨
    // 위 4개의 값은 
    // 각각 사각형의 오른족 변의 X좌표/왼쪽 변의 X좌표/아래쪽 변의 Y좌표/위쪽 변의 Y좌표를 담당
    Vector2 obstacle = Vector2(min_right - max_left, min_down - max_up);
    // 이렇게 만들어진 사각형의 변의 길이를 확인해서,
    // 둘 중 하나라도 0이거나 그 미만의 음수인 경우 이 사각형은 실존하지 않는다는 결론을 내릴 수 있음
    // 반대로, 둘 다 양수라면 이 사각형 = 충돌하는 범위는 실존한다는 결론을 내릴 수 있음

    if (obstacle.x > 0.f && obstacle.y > 0.f)
    {
        // overwrap = 이 함수 밖에서 충돌범위가 정확히 어떻게 되나 그 데이터를 받아올 때 사용할 주소
        // 만약 이게 입력되어 있다며느 위에서 구한 충돌범위를 여기다 입력해 함수 밖으로 반환함
        if (overwrap != NULL)
            *overwrap = obstacle;
        return true;
    }
    else
        return false;

    // 현 시점에서의 이 함수는 회전각이 얼마가 되든 상관치 않고
    // 항상 고정된 범위만을 충돌범위로 잡기 때문에 회전에 제대로 대응하지 못함

    // 회전할 때 만들어질 수 있는 제일 큰 사각형을 판정으로 잡는 것을 생각해볼 수도 있으나,
    // 이 경우엔 오히려 닿지 않았음에도 닿았다 판정되는 경우가 생길 가능성이 높기 때문에 힘들
    // -> 아예 회전을 담당하는 알고리즘은 다른 알고리즘으로 분리시켜서 필요할 때 그 쪽을 이용함
    // (그게 OBB 알고리즘)
}

bool RectCollider::isOBB(RectCollider* rect)
// Oriented Bounding Box의 약자
// 지향성 경계상자 - 회전방향을 따라가는 충돌판정 처리법

// 말로써 간단히 정리하자면 :
// 두 물체를 어떤 축에 "투영"(혹은 "사영")시켰을 때
// 투영된 두 물체가 서로 겹치지 않는다면
// 두 물체를 가로질러서 서로를 분리시키는 무언가의 분리축이 존재한다고 확정할 수 있음
// 그런 분리축이 존재하는지를 검사해서 존재한다면 충돌하지 않는 것,
// 없다면 충돌한 것이라 판단하는 충돌 검사법
{
    ObbDesc this_obb = GetObbDesc();
    // 내 충돌판정이 투영할 때 사용할 데이터를 생성
    // 정확히는 회전이 반영된 충돌판정 데이터

    ObbDesc rect_obb = rect->GetObbDesc();
    // 상대 충돌판정도 마찬가지

    // 두 충돌판정이 얼마나 회전했든, 그 충돌판정의 트랜스폼 자체가 가리키는 위와 오른쪽을 확인할 수 있도록
    // 해당 정보를 관리하는 인스턴스를 만들어 정리한 것

    Vector2 nea1 = this_obb.Axis[0];
    Vector2 nea2 = this_obb.Axis[1];
    Vector2 ea1 = nea1 * this_obb.half_size.x;
    Vector2 ea2 = nea2 * this_obb.half_size.y;
    // 두 사각형을 투영할 축을 만들 때 필요한 정보들을
    // 위의 ObbDesc에서 만들어진 회전이 반영된 충돌판정을 이용해 작성

    Vector2 neb1 = rect_obb.Axis[0];
    Vector2 neb2 = rect_obb.Axis[1];
    Vector2 eb1 = neb1 * rect_obb.half_size.x;
    Vector2 eb2 = neb2 * rect_obb.half_size.y;
    // 상대방 측의 축을 만들 때 필요한 정보도 마찬가지로 생성

    Vector2 distance = this_obb.pos - rect_obb.pos;
    // 두 충돌판정 사이의 거리를 저장

    // 앞으로, 두 충돌판정들이 각각 가지고 있는 오른쪽, 위를 보는 2개의 축을 이용해
    // 총 4개의 축을 기준으로 분리축이 존재하는지를 검증할 것

    // A : 나 자신, B : 상대 충돌판정
    // 테스트 축 : nea1(A.right)
    float lengthA = ea1.GetLength();
    // thjis_obb, 즉 나 자신의 현 충돌판정에서 오른쪽을 바라봤을 때의 값
    // 달리 말하면 나 자신의 충돌판정의 중앙에서 오른쪽 변 끝까지 직선으로 나갔을 때의 총 길이
    // 현재 테스트하는 기준측이 나 자신의 오른쪽이므로 그 길이를 온전히 이용할 수 있음
    // 그리고 위를 보는 방향의 길이는 이 축을 기준으로는 아예 좌우로 벗어나지 않으므로 0이 되어 무시 가능

    float lengthB = separateAxis(nea1, eb1, eb2);
    // 이 함수를 이용해 지금 기준측으로 사용하는 A.right축에
    // 상대방 축의 가로 길이와 세로 길이를 사영해 만들어진 두 그림자의 길이의 합을 여기에 계산

    float length = abs(Vector2::Dot(distance, nea1));
    // 축으로 사용할 기준선을 distacne(두 판정의 중앙점 사이의 거리)와
    // nea1(A.right, 지금 체크할 방향을 가리키는 단위 백터)를 이용해 내적하여 그 절대값을 취해
    // 우리가 사용할 기준선의 길이를 구한 것

    if (length > lengthA + lengthB)
        // 그렇게 구한 두 물체의 사영과 기준선의 길이를 비교해 기준선이 더 길다면
        return false; // 두 물체 사이에 빛이 통과할 틈이 존재한다 : 두 물체가 서로 떨어져있다는 의미이므로
    // 분리축이 존재한다는 결론을 내릴 수 있고, 하나라도 존재한다면 충돌하지 않는다는 것이니
    // 충돌하지 않았다고 판단

   // 분리축 : nea2(A.Up())
    lengthA = ea2.GetLength();
    lengthB = separateAxis(nea2, eb1, eb2);

    length = abs(Vector2::Dot(distance, nea2));

    if (length > lengthA + lengthB)
        return false;

    // 분리축 : neb1(B.right())
    lengthA = eb1.GetLength();
    lengthB = separateAxis(neb1, ea1, ea2);

    length = abs(Vector2::Dot(distance, neb1));

    if (length > lengthA + lengthB)
        return false;

    // 분리축 : neb2(B.Up())
    lengthA = eb2.GetLength();
    lengthB = separateAxis(neb2, ea1, ea2);

    length = abs(Vector2::Dot(distance, neb2));

    if (length > lengthA + lengthB)
        return false;

    return true;   // 어떤 상황에서도 겹친다면 충돌한다.
}

bool RectCollider::isAABB(CircleCollider* circle)
{
    Vector2 half = Size() * 0.5f;
    Vector2 closest; // 원과 사각형 사이에서 제일 가까운 거리 - ? 사각형에서 원의 중심에 제일 가까운 점의 위치

    if (circle->pos.x <pos.x - half.x) // 원의 중심점이 상자의 왼쪽 끝보다 더 왼쪽일 경우
        closest.x = pos.x - half.x;
    else if (circle->pos.x > pos.x + half.x) // 원의 중심점이 상자의 오른쪽 끝보다 더 오른쪽일 경우
        closest.x = pos.x + half.x;
    else
        closest.x = circle->pos.x;

    // 위의 내용을 Y좌표에 대해서도 실행
    if (circle->pos.y < pos.y - half.y) // 원의 중심점이 상자의 위쪽 끝보다 더 위쪽일 경우
        closest.y = pos.y - half.y;
    else if (circle->pos.y > pos.y + half.y) // 원의 중심점이 상자의 아래쪽 끝보다 더 아래쪽일 경우
        closest.y = pos.y + half.y;
    else
        closest.y = circle->pos.y;

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

bool RectCollider::isOBB(CircleCollider* circle)
{
    return circle->isRectCollision(this);
}

float RectCollider::separateAxis(Vector2 seperate, Vector2 e1, Vector2 e2)
// 현재 테스트하고 있는 축의 방향을 이용해,
// 해당 축을 사용하지 않는 상대측 판정범위에서
// 이 축을 기준선으로 사영했을 때 만들어지는 길이를 측정하는 함수
{
    float r1 = abs(Vector2::Dot(seperate, e1));
    float r2 = abs(Vector2::Dot(seperate, e2));
    // seperate라는, 현재 축을 만드는 방향을 가리키는 단위 백터를 기준으로 하여
    // e1과 e2가 각각 해당 방향 기준으로 얼마만큼의 좌표를(=값을) 가지고 있는지를
    // 내적을 통해 계산한 것

    return r1 + r2;
    // e1, e2는 각각 상대측의 2개 백터를 이용해 만들어낸 값들이므로
    // 상대방 측에서 사영한 총 길이는 이 값이 된다.
}

RectCollider::RectCollider(Vector2 size)
    :size(size)
{
    type = TYPE::RECT;

    CreateLine();
}

RectCollider::~RectCollider()
{
    delete VB;
}

RectCollider::ObbDesc RectCollider::GetObbDesc()
// 회전된 상태에서의 충돌판정의 범위를 정의하기 위해 필요한 데이터를 모아둔 구조
{
    // 이를 표현하기 위해 필요한 데이터는 총 4개
    obb_desc.pos = GlobalPos(); // 1. 충돌판정의 위치
    obb_desc.half_size = Size() * 0.5f; // 2. 충돌판정의 크기(좌우 및 상하의 절반)

    obb_desc.Axis[0] = Right();
    // 3. 이 충돌판정이 현재 보는 방향을 기준으로 오른쪽을 가리키는 단위백터
    obb_desc.Axis[1] = Up();
    // 4. 이 충돌판정이 현재 보는 방향을 기준으로 위쪽을 가리키는 단위백터

    return obb_desc;
}
