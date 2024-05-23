#pragma once
class Random : public Singleton<Random>
	// 이 프로그램 내부에서 시간 경과 등을 참조할 때 사용할 Singleton 클래스
	// 상속받은 클래스를 보면 탬플릿으로 지금 만들고자 하는 Timer라는 클래스를 이용하는 Singleton을
	// 이용하고 있음을 볼 수 있음
	// 이렇게 부모 클래스가 템플릿일 경우 템플릿 포멧에 자식클래스 그 자체를 넣는 것으로도 이용가능
{
private:
	Random();
	~Random();

	std::random_device rd;
public:
	friend class Singleton;
	
	int GetRandomInt(int min, int max);
	float GetRandomFloat(float min, float max);
};