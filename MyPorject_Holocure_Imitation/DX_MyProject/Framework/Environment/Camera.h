#pragma once
class Camera :public Transform
{
private:
	MatrixBuffer* view; // 뷰 변환을 이용하기 위해 만들어둔 버퍼
	// 기존에 Program에서 담당하고 있었던 내용들을 Environment와 여기로 옮겨서 처리할 예정

	float speed;

	Transform* target;

	Vector2 offset;
	// 여기서는 카메라가 화면 내에서 자리잡은 위치를 저장하는 것과 동시에,
	// 이런저런 용도로 사용할 값이 저장될 맴버변수
	// 이 값을 이용해서 전체 화면 중 어느 부분을 원점으로서 화면을 표시할 것인지를 지정

	Vector2 left_top;
	Vector2 right_bottom;

public:
	Camera();
	~Camera();

	void Update();
	void PostRender();

	void SetPos(Vector2 pos)
	{
		this->pos = offset + pos;
	}

	void SetTarget(Transform* target)
	{
		this->target = target;
	}

private:
	void FreeMode();
	void FollowMode();

	void SetView();
};