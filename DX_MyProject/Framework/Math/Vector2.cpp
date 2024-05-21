#include "framework.h"

// 기본적으로 2차원 백터(수학적 의미)를 다루는 클래스이므로
// x값, y값 2개만 작성하면 끝
// 이 2개의 값은 부모 클래스(=구조체)인 Float2에서 다루는 애용이므로
// 부모 클래스의 생성자를 위임 생성자로서 이용하면 끝

Vector2::Vector2():Float2(0,0)
{
}

Vector2::Vector2(float x, float y) :Float2(x,y)
{
}

Vector2::Vector2(Float2 value):Float2(value)
{
}

Vector2 Vector2::operator+(const Vector2& value) const
{
	return Vector2(x + value.x, y + value.y);
}

Vector2 Vector2::operator-(const Vector2& value) const
{
	return Vector2(x - value.x, y - value.y);
}

Vector2 Vector2::operator*(const Vector2& value) const
{
	return Vector2(x * value.x, y * value.y);
}

Vector2 Vector2::operator/(const Vector2& value) const
{
	return Vector2(x / value.x, y / value.y);
}

Vector2 Vector2::operator*(const float& value) const
{
	return Vector2(x * value, y * value);
}

Vector2 Vector2::operator/(const float& value) const
{
	return Vector2(x / value, y / value);
}

void Vector2::operator+=(const Vector2& value)
{
	x += value.x;
	y += value.y;
}

void Vector2::operator-=(const Vector2& value)
{
	x -= value.x;
	y -= value.y;
}

void Vector2::operator*=(const float& value)
{
	x *= value;
	y *= value;
}

void Vector2::operator/=(const float& value)
{
	x /= value;
	y /= value;
}

// 단위 백터 : 백터의 크기(=길이)가 1인 백터
// 기본적으로 공간상의 좌표나 움직임 등을 자료로서 표시할 때는
// "원점"에서 x축, y축 각각으로 얼마만큼 떨어져있는 자리에 있는지를 표기(=백터의 정의)
// 이 백터는 기본적으로 같은 방향을 가리키고 있다 하더라도 그 백터의 길이에 따라서 좌표값이 달라질 수 있으며,
// 그 길이는 해당 방향으로 얼마나 빠른 속도로 가는지 등의 물리량을 담당하는 정보이기도 함

// 그리고 그런 물리량이 필요하지 않고 오로지 해당 백터가 가리키는 방향이 어느 방향인지만 필요한 경우가 상당히 많음
// 따라서, 하나의 백터가 주어졌을 때 그 백터의 길이랑 상관없이 가리키는 방향만을 구할 방도가 필요
// 그 때 사용되는 것이 이 단위백터
// 모든 백터는 같은 방향을 가리키는 단위 백터에 실수를 곱한 값으로서 표현이 가능하나,
// 일단 그 방향을 가리키는 단위 백터만 구하면 길제 이동거리 등은 거기에 적당한 값을 곱해서 구하는 식

// 실제로는 이미 거리 등이 주어진 상황에서 단위백터를 구한 뒤 이를 이용해야 하는 경우가 더 많아,
// 그 단위 백터를 구하거나 단위 백터로 만드는 함수들이 바로 밑의 2개

void Vector2::Normalize() // 이 백터를 단위 백터로 만드는 함수 - 백터를 표준화하는 함수
{
	float length = GetLength();	// 헤더 쪽에 미리 정의해뒀던, 백터의 길이(=크기=거리)를 구하는 함수를 이용
	x /= length;
	y /= length;

	// 위에도 이야기 했듯, 단위 백터는 길이가 1인 백터
	// 그리고 단위 백터가 아닌 백터는 단위 백터에 특정 값(=백터의 크기)을 곱한 것으로 표현할 수 있음
	// 그러니 그 특정 값을 x좌표와 y좌표 각각에서 나누는 것으로 단위 백터를 구할 수 있다
	// 이 함수는 그렇게 단위 백터를 구하는 동시에 이 백터 자체를 단위 백터로 만드는 것
}
// 그러나 실제로는 백터 자페를 표준화시켜야 할 일은 많지 않고,
// 특정 백터가 어느 방향을 가리키는지 그 단위 백터를 구하기만 하는 일이 더 많음

Vector2 Vector2::Normalized() const // 이 백터의 단위 백터를 구하는 함수
// 구하기만 하는 것이므로 const를 선언함으로서 이 백터가 가진 데이터 자체는 수정할 수 없게 만들어야 함
{
	float length = GetLength();
	return Vector2(x / length, y / length);
}

float Vector2::Angle() const // 이 백터의 각도를 구하는 함수
{
	return atan2(y, x);
	// x, y 값만으로 어떻게 각도를 구하는지는 삼각함수의 arctan2(y,x) 등을 찾아보는 것을 권장
}

Vector2 Vector2::TransformCoord(const Vector2& vec, const Matrix& mt)
// 백터와 행렬을 곱할 때 사용하는 함수
{
	XMVECTOR temp = XMLoadFloat2(&vec);
	temp = XMVector2TransformCoord(temp, mt);

	Vector2 temp_pos;
	XMStoreFloat2(&temp_pos, temp);

	return temp_pos;
	// 이런 함수들을 이용해서 DX에서 백터와 행렬의 계산을 지원한다고만 기억하면 됨
}
