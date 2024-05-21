#pragma once
class Timer : public Singleton<Timer>
// 이 프로그램 내부에서 시간 경과 등을 참조할 때 사용할 Singleton 클래스
// 상속받은 클래스를 보면 탬플릿으로 지금 만들고자 하는 Timer라는 클래스를 이용하는 Singleton을
// 이용하고 있음을 볼 수 있음
// 이렇게 부모 클래스가 템플릿일 경우 템플릿 포멧에 자식클래스 그 자체를 넣는 것으로도 이용가능
{
private:
	Timer();
	~Timer();

public:
	friend class Singleton;
	// friend : 간단히 말하면 private 자유이용권
	// firend class로 선언한 클래스는
	// 이 클래스의 내부에서 해당 클래스의 private, protected 등을 자유롭게 사용할 수 있음

	// Singleton의 Get() 함수를 이용할 때, 위 구문이 없으면
	// 이 Control 함수에서는 Singleton의 instance에 접근할 수가 없어서
	// 아예 Get 함수 자체를 이용할 수가 없음

	float time_scale; // 1초를 표현하는데 필요한 "성능 카운터"
	float time_elapsed; // 경과된 시간을 체크하는 멤버

	// 밑의 2개는 타임 스탬프로 사용할 변수 2개
	// 자료형은 long long int -> 64비트를 사용하는 int
	__int64 cur_time; 
	__int64 last_time;  
	__int64 period_frequency;
	// 현재 컴퓨터의 사양이 메인 루프를 몇 번 돌릴 수 있는지를 저장하는 변수

	int frame_rate; // FPS
	int frame_count; // 프로그램 시작 후 경과된 프레임의 개수

	float one_sec_count; // 1초가 지났는지의 여부를 저장하는 변수
	float run_time; // 프로그램이 실행되기 시작한 후 얼마나 시간이 흘렀는지 저장하는 변수

	void Update();

	int GetFPS() { return frame_rate; } // FPS 출력 함수 
	float GetDeltaTime() { return time_elapsed; } // 이번 틱에 경과된 시간을 반환하는 함수
	float GetRunTime() { return run_time; } // 프로그램 실행 후 경과된 시간을 반환하는 함수

};