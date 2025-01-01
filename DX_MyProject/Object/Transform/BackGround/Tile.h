#pragma once
class Tile :public BackgroundObject
{
private:
	static vector<shared_ptr<const Frame>>& GetTileFrames();
	static int& GetTileUseCnt();

private:

public:
	Tile(int inIdx=0, Vector2 inRenderSize = Vector2(128.0f, 128.0f));
	~Tile();

	void Update();
	void Render();
	
	void InitFrame();
	void ClearFrame();

	void SetActive(bool active);

};