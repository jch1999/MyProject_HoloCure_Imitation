#include "framework.h"
#include "Control.h"

Control::Control()
	: cur_state{}, old_state{}, map_state{}
	// 타겟 생성자로도 배열 역시 위와 같이 초기화 가능
{
}

Control::~Control()
{
}

void Control::Update()
{
	memcpy(old_state, cur_state, sizeof(old_state));
	// 왼쪽 포인터에 오른쪽 포인터가 가지고 있는 값들을 복사하는 함수
	// 복사하는 범위는 old_state가 가지고 있는 용량만큼
	// = 업데이트를 하는 시점에 기존 상태를 갱신

	GetKeyboardState(cur_state);
	// BYTE[255] 배열에 현 시점의 키보드 중 어느 키가 눌렸는지를 전부 기록하는 함수를 이용해
	// 각 키가 현재 눌려있는지의 여부를 저장

	// 시스템에서 키보드의 각 키가 눌렸을 떄 정보가 어떻게 저장되는지 설명하자면
	// 키가 눌려있을 경우 해당 키에 대응하는 값은 128 || 129 중 하나를 가지고 있음
	// 눌려있지 않을 경우엔 0 || 1 중 하나를 가지고 있다
	// 시스템상에선 각 키가 눌릴 때마다 128 -> 0 -> 129 -> 1의 순서대로
	// 대응하는 값이 변동하면서 순환되는 것으로 눌림/안눌림을 체크하고 있음

	for (int i = 0; i < KEY_MAX; i++)
	{
		BYTE key = cur_state[i] & 0x80;
		// 0x80 == 128, 시스템에서 해당 키가 눌려있을 경우 할당되는 값

		cur_state[i] = key ? 1 : 0;
		// 키가 눌려있다면 cur_state는 128이나 129 중 하나의 값을 가짐
		// 0x80 || 0x81
		// 둘 중 어느 값이더라도 같은 코드에서 똑같이 대응하도록 만들기 위해
		// 위의 key로 가공을 하고,
		// 이 과정에서 0x80의 비트를 제외하면 그 어떤 값도 남지 않도록 하여
		// 해당 비트가 1이면 눌렸고 0이면 눌리지 않았다 판단하도록 저장

		BYTE old = old_state[i];
		BYTE cur = cur_state[i];
		// 현재 검사하는 키가 직전에 눌렸는지 + 현재 눌려있는지 각각을 체크하는 변수

		if (old == 0 && cur == 1) // 좀전까지 안 눌렸다가 지금은 눌렸다 : DOWN
		{
			map_state[i] = DOWN;
		}
		else if (old == 1 && cur == 1) // 계속해서 눌려왔다 : PRESS
		{
			map_state[i] = PRESS;
		}
		else if (old == 1 && cur == 0) // 눌리고 있었다가 지금 뗴졌다 : UP
		{
			map_state[i] = UP;
		}
		else // 다 아니다 = 애초에 눌려있지 않았다 : NONE
		{
			map_state[i] = NONE;
		}

	}

}
