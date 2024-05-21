#include "framework.h"

Camera::Camera()
    :speed(200.0f), target(nullptr), offset(Vector2(0, 0))
{
    view = new MatrixBuffer();
}

Camera::~Camera()
{
    delete view;
}

void Camera::Update()
{
    if (target != NULL) // 현재 주시중인 대상이 있으면
    {
        FollowMode();
    }
    else // 없으면
        FreeMode();

    // 어느 쪽이건 실행해서 카메라의 위치가 확정되었으면
    // 뷰 행렬을 업데이트
    SetView();
}

void Camera::PostRender()
{
}

void Camera::FreeMode() // 카메라를 자유로이 움직일 수 있는 모드
{
    if (KEY_CON->Press(VK_RBUTTON)) // 오른쪽 마우스 버튼이 눌리고 있는 동안
    {
        if (KEY_CON->Press('W')) // 위 
        {
            if (offset.y >= 0)
                offset.y -= speed * DELTA;
            // 카메라의 pos 값이 아닌 오프셋을 통해 관리하고 있음
            // 왜 오프셋을 이용해 관리하는가? :
            // 카메라의 pos 값은 우리가 화면에 출력하고자 하는 범위가
            // 어디에서 시작되는지를 기록하기 위한 것
            // 이는 실제 공간상에서의 카메라의 정확한 좌표를 드러내는 것이 아니기 때문에,
            // 실제 공간상에서의 좌표를 추가로 다루는 맴버(offset)을 이용해 안전하게 쓰고자 함

            // 여튼, 그 오프셋을 통해서 카메라가 있을 수 있는 영역을 제한하고
            // 그 범위 내에서 키보드 입력을 통해 그 좌표값을 변동시키는 것
        }
        if (KEY_CON->Press('S')) // 아래
        {
            if (offset.y <= (float)WIN_HEIGHT / 2.0f)
                offset.y += speed * DELTA;
        }
        if (KEY_CON->Press('A')) // 왼쪽
        {
            if (offset.x >= 0)
                offset.x -= speed * DELTA;
        }
        if (KEY_CON->Press('D')) // 오른쪽
        {
            if (offset.x <= (float)WIN_WIDTH / 2.0f)
                offset.x += speed * DELTA;
        }
    }

    pos = offset; // 위에서 이용했던 offset의 데이터를 그대로 여기에 입력
    left_top = pos;
    // 현재 이 카메라가 가리키고 있는 공간이
    // 실제 좌표로는 정확히 어디인지를 따로 보관헤두기 위해 저장
    right_bottom = pos + Vector2((float)WIN_WIDTH / 2.0f, (float)WIN_HEIGHT / 2.0f);
    // 오른쪽 아래는 왼쪽 위의 정보를 가진 pos를 이용해 연산하여 저장
    // 다만, 지금 쓰고 있는 이 값들은 어디까지나 현 시점에서 사용하고자 하는
    // 화면의 크기에 불과하며, 여기에 있는 값은 앞으로 변할 수 있음
}

void Camera::FollowMode() // 카메라가 특정 타겟을 쫒아가는 모드
{
    Vector2 target_pos = target->GlobalPos() - Float2((float)WIN_WIDTH / 2.0f, (float)WIN_HEIGHT / 2.0f);
    // 타겟의 위치를 전체 좌표계 기준으로 받고
    // 그 위치에서 특정 값(offset?)을 빼서 실제 카메라의 위치를 그 위치에 맞게 조정
    // 카메라의 위치를 나타낸느 pos 값은 카메라가 보여주기 시작하는 위치,
    // 즉 화면으로 치면 왼쪽 위 끝부분의 좌표값을 적는 부분이기 때문에
    // 타겟으로 삼는 대상이 정중앙에 오도록 하려면
    // 타켓의 위치에서 화면 전체 크기의 절반만큼을 빼내어 
    // 화면상에서의 위치가 어디가 될 것인지를 연산해야 할 필요가 있음

    // 여기서 보정하는 값을 얼마로 하느냐에 따라 
    // 따라가는 대상이 화면의 어디에 위치해있는지를 조절할 수 있음
    // 나중에 카메라가 따라가는 대상을 다른 오브젝트로 잡거나
    // 따라가는 방식을 정중앙이 아닌 다은 방식으로 할 때 고려해볼 것

    offset = pos = LERP(pos, target_pos, speed / 100.0f * DELTA);
    // 그래서 나온 것이 바로 이 부분 : 계산한 위치를 pos과 offset에 기록
    // LERP : 1차원에서 사용되는 선형 보간 
    // 제논의 역설 중에 이런 역설이 있음
    // 100m 달리기 육상 선수가 100m 달리기 시작했을 때,
    // 결승점에 도달하려면 당연히 출발점에서 도착점까지의 길이 중 절반인
    // 50m 지점에 도달해야 함
    // 거기에 도달한 뒤로는 결승점에 도달하기 위해 75m 지점을 통과해야 하고,
    // 87.5m , 93.75m, 96.905m, ... 같은 식으로 계속해서 다음 중간점을 지나야 함

    // 역설 자체는 이런 이유로 선수는 결승점에 도달할 수 없다, 라는 이론이지만
    // 이게 중요한 건 아니고 중요한 건 이것처럼 전체 구간에서 매 구간구간을
    // 위와 같이 쪼갤 수 있다는 점이 중요

    // 그냥 단순하게 등속 운동을 하고 있다면
    // A에서 B까지 가는데 항상 일정한 속도로 일정한 시간을 움직이다가
    // 도착하면 그대로 거기서 멈추게 될 것
    // 이는 실제로 움직일 때는 도착지를 살짝 넘어가서 다시 돌아가거나
    // 도착하기 직전까지 속도가 점차 줄어들거나 하는 
    // 그런 현실적인 움직임과는 괴리감이 있음
    // 따라서 그런 현실적인 움직임을 보여줘야 하는 액션게임 등에서는
    // 남아있는 거리 등에 따라서 움직이는 속도를 실시간으로 바꾸는 보간 작업을
    // 진행해야 하는 경우가 있다

    // 그 중에서도 단순히 거리를 좁혀나갈 때 사용하는 보간 계산식이
    // 위에서 사용하고 있는 LERP

    // 식은 다음과 같음 : start + ( end - start ) * ratio
    // -> 시작 지점에서 종료 지점까지 방향백터를 따라가되,
    // 한 번 호출되었을 때 따라가는 양은 전체 길이에서 입력된 ratio의 값에 비례하여
    // 그 길이가 정해진다

    // 비율이므로 ratio에 들어가는 값은 반드시 0~1 사이의 값이 되어야 
    // 정상적인 작동을 보장함

    left_top = pos;
    right_bottom = pos + Vector2((float)WIN_CENTER_X / 4.0f, (float)WIN_CENTER_Y * 3.0f / 2.0f);
}

void Camera::SetView()
// 카메라의 위치 등을 저장한 뷰 행렬을 만들어내는 과정
// 만들어 낸 후에는 셰이더에 등록해서 사용
{
    WorldUpdate();
    Matrix inv_view = XMMatrixInverse(NULL, world);
    // 뷰 행렬은 WVP 계산을 하려고 구할 때
    // 계산을 끝낸 월드 행렬에 역행렬을 구해서 만듦

    view->Set(inv_view);
    view->SetVS(1);
}
