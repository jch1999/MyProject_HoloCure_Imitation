#pragma once

class ScrollImageRect : public Transform
{
private:
	ScrollRectUV* image;

	ID3D11ShaderResourceView* srv;

	Float2 scroll_speed;

public:
	ScrollImageRect(Vector2 pos = Vector2(0, 0), Vector2 size = Vector2(0, 0), Vector2 scale = Vector2(1, 1),
		float angle = 0.0f, Matrix* parent = NULL);
	~ScrollImageRect();

	bool SetImage(LPCWSTR file_loc);
	void SetScrolling(Float2 scroll_speed);

	void Update();
	void Render();

};