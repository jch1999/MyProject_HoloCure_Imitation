#pragma once
// DirectX���� �����ϰ� �մ� ����ü�� Flaot2�� �츮�� �� �� ��Ȱ�� ����� �� �ְ� �����ϴ� Ŭ����
// Float2 : DirectX���� �����ϰ� �մ� �Ǽ� 2���� �����ϴ� ����ü
// Ŭ������ �ƴ϶� ����ü�� ſ�� ����ϱⰡ �� ������ �κ��� ����
// �׷��� �츮�� �� ����ü�� ����� Ŭ������ ����� ���� �����ڿ� ���� �����ε��� �����α� ���� �뵵

class Vector2 : public Float2
{
	// private�� �������� ���� : Float2�� �����ʹ� �״�� ����
	// �ű⿡ ���� �Լ����� �־ �ս��� �̿��ϱ� ���� Ŭ�����̱� ����

public:
	Vector2();
	Vector2(float x, float y);
	Vector2(Float2 value);
	// Vector2 �ڱ� �ڽ��� �Ű������� �޴� ���� ������

	// Vector2�� ������ �����ε��� �����ϴ� ����
	// Float2��� ����ü�� ������ �����ε��� �Ǿ����� �ʾұ� ������, ���� Float2 ����ü�� ����ִ� �����͵���
	// ������ �� ������ Float.x, Float.y ���� ������ �����ͼ� �̿��ϰ� ���� ���� �����ϴ� ������ �̿��ؾ� ����\
	// DX���� �����ϴ� �Լ��� �Ϻ� �����ϱ�� ������, ������ �� ������������ �ƿ� �����츮�� ����� ��
	Vector2 operator+(const Vector2& value)const;
	Vector2 operator-(const Vector2& value)const;
	Vector2 operator*(const Vector2& value)const;
	Vector2 operator/(const Vector2& value)const;

	Vector2 operator*(const float& value)const;
	Vector2 operator/(const float& value)const; // �Ű����� Ÿ�� �տ� const�� ���� ��� �ش� ���� ������ �� ���� ����
	// �Լ� �ڿ� const�� ���� ���
	// "�� �Լ��� �� �Լ��� �Ҹ� Ŭ���� �ν��Ͻ��� �� � ���뵵 �ٲ��� �ʰڴ�"��� ����
	// -> �ش� �Լ� �������� �� Ŭ������ �� � �ɹ��� ���� �ٲ� �� ����

	void operator+=(const Vector2& value);
	void operator-=(const Vector2& value);
	void operator*=(const float& value);
	void operator/=(const float& value);

	float GetLength()const
	{
		return sqrt(x * x + y * y);
	}// �� ������ ����(��Į�� �� = ������ ������ ���� ������ ��ġ)�� ����� ��ȯ�ϴ� �Լ�

	void Normalize(); // �� ���͸� ǥ��ȭ��Ű�� �Լ�
	Vector2 Normalized()const;
	// �� ���Ͱ� ǥ��ȭ�Ǿ��� ������ ��� � ���� �Ǵ��� ��ȯ�ϴ� �Լ�

	float Angle() const; // �� ���Ͱ� ���ϴ� ������ ����ϴ� �Լ�

	static float Dot(const Vector2& v1, const Vector2& v2)
	{
		return v1.x * v2.x + v1.y * v2.y;
	}// �� ���͸� �����ϴ� �Լ�
	// static�� �پ������Ƿ� ���� �Լ��� ����

	static Vector2 TransformCoord(const Vector2& vec, const Matrix& mt);
	// ���߿� �� �Լ��� ����� ���� �� �� ����
};