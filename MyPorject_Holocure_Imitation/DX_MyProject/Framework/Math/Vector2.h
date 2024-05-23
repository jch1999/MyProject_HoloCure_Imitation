#pragma once
// DirectX에서 제공하고 잇는 구조체인 Flaot2를 우리가 좀 더 원활히 사용할 수 있게 보완하는 클래스
// Float2 : DirectX에서 제공하고 잇는 실수 2개를 저장하는 구조체
// 클래스가 아니라 구조체인 탓에 사용하기가 좀 불편한 부분이 많음
// 그래서 우리가 이 구조체를 상속한 클래스를 만들고 각종 연산자에 대한 오버로딩을 만들어두기 위한 용도

class Vector2 : public Float2
{
	// private은 존재하지 않음 : Float2의 데이터는 그대로 쓰고
	// 거기에 각종 함수들을 넣어서 손쉽게 이용하기 위한 클래스이기 때문

public:
	Vector2();
	Vector2(float x, float y);
	Vector2(Float2 value);
	// Vector2 자기 자신을 매개변수로 받는 복사 생성자

	// Vector2의 연산자 오버로딩을 정의하는 과정
	// Float2라는 구조체는 연산자 오버로딩이 되어있지 않았기 때문에, 같은 Float2 구조체에 들어있는 데이터들을
	// 연산할 땐 일일이 Float.x, Float.y 같은 식으로 꺼내와서 이용하고 각각 따로 저장하는 식으로 이용해야 했음\
	// DX에서 연산하는 함수를 일부 지원하기는 했으나, 불편한 건 마찬가지여서 아예 직접우리가 만드는 것
	Vector2 operator+(const Vector2& value)const;
	Vector2 operator-(const Vector2& value)const;
	Vector2 operator*(const Vector2& value)const;
	Vector2 operator/(const Vector2& value)const;

	Vector2 operator*(const float& value)const;
	Vector2 operator/(const float& value)const; // 매개변수 타입 앞에 const를 붙일 경우 해당 값을 수정할 수 없게 막음
	// 함수 뒤에 const를 붙일 경우
	// "이 함수는 이 함수가 불린 클래스 인스턴스의 그 어떤 내용도 바꾸지 않겠다"라는 서언
	// -> 해당 함수 내에서는 이 클래스으 그 어떤 맴버의 값도 바꿀 수 없음

	void operator+=(const Vector2& value);
	void operator-=(const Vector2& value);
	void operator*=(const float& value);
	void operator/=(const float& value);

	float GetLength()const
	{
		return sqrt(x * x + y * y);
	}// 이 백터의 길이(스칼라 값 = 방향을 가지지 않은 순수한 수치)를 계산해 반환하는 함수

	void Normalize(); // 이 백터를 표준화시키는 함수
	Vector2 Normalized()const;
	// 이 백터가 표준화되었다 가정할 경우 어떤 값이 되는지 반환하는 함수

	float Angle() const; // 이 백터가 향하는 각도를 출력하는 함수

	static float Dot(const Vector2& v1, const Vector2& v2)
	{
		return v1.x * v2.x + v1.y * v2.y;
	}// 두 백터를 내적하는 함수
	// static이 붙어있으므로 전역 함수로 사용됨

	static Vector2 TransformCoord(const Vector2& vec, const Matrix& mt);
	// 나중에 이 함수를 사용할 날이 올 때 설명
};