#pragma once
class Program
	// DirectX의 본격적인 실행을 관리할 인스턴스로서 사용되는 클래스

	// 지금은 맴버도 함수도 간단하나, DirectX를 차차 구축해나가면서 여기에 추가되는 내요이 점차 많아질 예정
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