#pragma once
class Tile :public Transform
{
private:
	static vector<shared_ptr<const Frame>> tileFrames;
	static int TileUseCnt;

private:
	int idx;
	shared_ptr<const Frame> frame;

	VertexShader* VS;
	PixelShader* PS;
	ColourBuffer* CB;

public:
	Tile(int idx);
	~Tile();

	void Update();
	void Render();
	void PostRender();
	
	void InitFrame();
	void ClearFrame();

	void SetActive(bool active);

private:
	FORCEINLINE static shared_ptr<const Frame> GetFrame(int index) { return tileFrames[index]; }
};