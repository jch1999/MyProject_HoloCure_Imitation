#pragma once
#pragma once
class ScrollRectUV : public Shape
{
private:
	D3D11_PRIMITIVE_TOPOLOGY type;

	Float2 scroll_speed;

public:
	ScrollRectUV(Vector2 size, Float2 scroll_speed,
		D3D11_PRIMITIVE_TOPOLOGY type = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	~ScrollRectUV();


	D3D11_PRIMITIVE_TOPOLOGY GetType() { return type; }
	void Update();
	void Render();

	void SetScrollSpeed(Float2 speed) { this->scroll_speed = speed; }
};