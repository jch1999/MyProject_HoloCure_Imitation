#pragma once
class SunLight :public Transform
{
private:
	Transform* target;
	Vector2 offset;
	vector<Clip*> clips;
	int clip_idx;
	Vector2 render_size;

	VertexShader* VS;
	PixelShader* PS;
	ColourBuffer* CB;

public:
	SunLight();
	~SunLight();

	void Update();
	void Render();
	void PostRender();
	void SetIndex(int idx);
	void SetTarget(Transform* t) { target = t; }
	void SetOffset(Vector2 offset) { this->offset = offset; }
};