#pragma once
class Random : public Singleton<Random>
	// �� ���α׷� ���ο��� �ð� ��� ���� ������ �� ����� Singleton Ŭ����
	// ��ӹ��� Ŭ������ ���� ���ø����� ���� ������� �ϴ� Timer��� Ŭ������ �̿��ϴ� Singleton��
	// �̿��ϰ� ������ �� �� ����
	// �̷��� �θ� Ŭ������ ���ø��� ��� ���ø� ���信 �ڽ�Ŭ���� �� ��ü�� �ִ� �����ε� �̿밡��
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