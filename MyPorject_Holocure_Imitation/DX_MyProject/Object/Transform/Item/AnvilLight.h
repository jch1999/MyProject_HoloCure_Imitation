#pragma once
class AnvilLight :public Transform
{
public:
protected:
	VertexShader* VS;
	PixelShader* PS;
	ColourBuffer* CB;

	Vector2 size;
	Vector2 offset;

	vector<Clip*> clips; // �ִϸ��̼� Ŭ����
	int clip_idx;

public:
	AnvilLight(Vector2 pos);
	 ~AnvilLight();

	void Update();
	void Render();
	void PostRender();
	void Respawn();

	void SetPos(Vector2 pos);
};