#pragma once
class Program
	// DirectX�� �������� ������ ������ �ν��Ͻ��μ� ���Ǵ� Ŭ����

	// ������ �ɹ��� �Լ��� �����ϳ�, DirectX�� ���� �����س����鼭 ���⿡ �߰��Ǵ� ������ ���� ������ ����
{
private:
	//Scene* scene;
	vector<Scene*> scenes;
	int scene_idx;

public:
	Program();
	~Program();

	void Update();
	void Render();

	void Create();
	void Delete();
};