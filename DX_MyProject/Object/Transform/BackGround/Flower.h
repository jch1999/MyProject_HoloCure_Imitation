#pragma once
class Flower :public BackgroundObject
{
protected:
	static vector<shared_ptr<const Frame>>& GetFlowerFrames();
	static int& GetFlowerUseCnt();

public:
	Flower(Vector2 inRenderSize = Vector2(29.0f, 38.0f) * 1.2f, float inSpawnRate = 0.35f);
	~Flower();

	virtual void Update() override;
	virtual void Render() override;
	void InitFrame();
	void ClearFrame();
};