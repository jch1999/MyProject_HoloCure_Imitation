#pragma once
class ItemLight :public Transform
{
public:
	static shared_ptr<const Frame>& GetItemLightFrame();
	static int& GetItemLightUseCnt();

protected:
	VertexShader* VS;
	PixelShader* PS;
	ColourBuffer* CB;

	Vector2 size;
	Vector2 offset;

public:
	ItemLight(Vector2 pos);
	 ~ItemLight();

	void Update();
	void Render();
	void PostRender();
	void Respawn();
	void InitFrame();
	void ClearFrame();

	void SetPos(Vector2 pos);
	void SetOffset(Vector2 offset) { this->offset = offset; }
};