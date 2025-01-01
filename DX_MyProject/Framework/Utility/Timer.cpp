#include "framework.h"
#include "Timer.h"

Timer::Timer()
	: frame_rate(0), frame_count(0), time_elapsed(0), one_sec_count(0), run_time(0)
{
	QueryPerformanceFrequency((LARGE_INTEGER*)&period_frequency);
	// 기본적으로 wWinMain 함수는 굉장히 빠른 빈도로 반복되고 있음
	// 그 반복되는 횟수가 초당 얼마인지를 확인하여 매개변수로 입력받은 포인터에 저장하는 함수
	// -> 현재 컴퓨터의 사양이 메인 루프를 초당 몇 번 돌릴 수 있는지를 검사하는 함수

	QueryPerformanceCounter((LARGE_INTEGER*)&last_time);
	// 성능 카운터가 현재 가지고 있는 값
	// = 시스템상으로 기록된 현재 시각을 받아오는 함수

	time_scale = 1.0f / (float)period_frequency;
	// long long int인 period_frequency를 1초에서 나누는 것으로
	// 1개의 카운터가 대략적으로 0.몇초인지를 여기서 계산해 저장

}

Timer::~Timer()
{
}

void Timer::Update()
{
	QueryPerformanceCounter((LARGE_INTEGER*)&cur_time);
	// 현재시각 저장

	time_elapsed = (float)(cur_time - last_time) * time_scale;
	// 마지막으로 기록된 성능 카운터를 현재 시점의 성능 카운터에서 빼고
	// 그렇게 구한 카운터의 변동값에 time_scale을 곱해 실제 경과된 시간을 체크
	if (time_elapsed > 0.1f)
		time_elapsed = 0.1f;
	// 지체된 시간이 과할 경우 그 값을 보정해 최소치로 만든다

	last_time = cur_time;

	frame_count++;
	// 1초당 몇 번의 작업이 진행되었는지 우리가 직접 체크

	one_sec_count += time_elapsed;
	// 경과한 총 시간을 계속해서 누적 저장

	if (one_sec_count >= 1.0f) // 총 1초가 경과되었나 확인
	{
		frame_rate = frame_count;
		one_sec_count = 0.0f;
		frame_count = 0;
		// 1초가 경과되었다면 현 시점의 초당 프레임 레이트를 갱신하고
		// 연산에 사용된 값들을 초기화
	}

	run_time += time_elapsed;
	// 이번 업데이트에 걸린 총 시간을 run_time에 기록
}
