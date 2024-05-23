#pragma once
#define KEY_MAX 255
// 일반적인 키보드의 키는 많아봐야 108개
// -> 255개의 값이면 그걸 절반으로 나눈 128개 데이터의 영역 2개로서 키를 표현할 수 있음

class Control : public Singleton<Control>
{
private:
	friend class Singleton;
	// friend : 간단히 말하면 private 자유이용권
	// friend class로 선언한 클래스는
	// 이 클래스의 내부에서 해당 클래스의 private, protected 등을 자유롭게 사용할 수 있음

	// Singleton의 Get() 함수를 이용할 떄, 위 구문이 없으면
	// 이 Control 함수에서는 Singleton의 instance에 접근할 수가 없어서
	// 아예 Get 함수 자체를 이용할 수가 없음

	enum {
		NONE,
		DOWN,
		UP,
		PRESS,
		MAX
	};
	// 특정 키의 현재 상태를 의미
	// 위에서부터 "눌리지 않음" / "지금 눌렸음" / "지금 뗴졌음" / "지금 눌리고 있음"을 의미

	BYTE cur_state[KEY_MAX]; // 현재 키보드가 눌려있는 여부를 저장하는 칸
	BYTE old_state[KEY_MAX]; // 마지막에 키보드가 눌려있었던 여부를 저장하는 칸
	BYTE map_state[KEY_MAX]; // 위 2개의 정보를 이용해 최종적으로 각 키의 현재 버튼 상태를 확인,
	// 확인한 결과를 저장하는 칸

	// 키보드의 각 키가 입력되었는지의 여부를 판단할 떄 사용할 비트 플래그들
	// 단, 총 108개 이상의 키를 인식할 예정 = 키보드의 모든 값을 인식할 예정이다

	Control();
	~Control();

public:
	void Update();

	bool Down(UINT key) { return map_state[key] == DOWN; }
	bool Up(UINT key) { return map_state[key] == UP; }
	bool Press(UINT key) { return map_state[key] == PRESS; }
};
// 프로그램에서 키보드 등의 입력장치 데이터를 관리하는 매니저