#pragma once
class ItemLight :public Transform
{
public:
protected:
	VertexShader* VS;
	PixelShader* PS;
	ColourBuffer* CB;

	Vector2 size;
	Vector2 offset;

	vector<Clip*> clips; // 애니메이션 클립들
	int clip_idx;

public:
	ItemLight(Vector2 pos);
	 ~ItemLight();

	void Update();
	void Render();
	void PostRender();
	void Respawn();

	void SetPos(Vector2 pos);
	void SetOffset(Vector2 offset) { this->offset = offset; }
};