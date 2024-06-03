#pragma once
class Tile :public Transform
{
private:
	int idx;
	vector<Clip*> clips;

	VertexShader* VS;
	PixelShader* PS;
	ColourBuffer* CB;

public:
	Tile(int idx);
	~Tile();

	void Update();
	void Render();
	void PostRender();
	void SetActive(bool active);
};