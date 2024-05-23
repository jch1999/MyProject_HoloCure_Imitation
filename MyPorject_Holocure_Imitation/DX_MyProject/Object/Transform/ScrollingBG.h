#pragma once

class ScrollingBG : public Transform
{
private:
	Quad* image[2];
	float speed;
	Vector2 size;

	// ID3D11ShaderResourceView* srv; - Quad에서 사용 중

public:
	ScrollingBG(Vector2 pos = Vector2(0, 0), Vector2 size = Vector2(0, 0), Vector2 scale = Vector2(1, 1),
		float angle = 0.0f, Matrix* parent = NULL);
	~ScrollingBG();

	void Update();
	void Render();
};