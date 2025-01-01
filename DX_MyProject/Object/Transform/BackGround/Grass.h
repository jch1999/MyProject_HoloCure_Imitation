#pragma once
class Grass:public BackgroundObject
{
protected:
	static vector<shared_ptr<const Frame>>& GetGrassFrames();
	static int& GetGrassUseCnt();

public:
	Grass(Vector2 inRenderSize = Vector2(29.0f, 30.0f), float inSpawnRate = 0.05f);
	~Grass();

	virtual void Update() override;
	virtual void Render() override;

	virtual void InitFrame() override;
	virtual void ClearFrame() override;
};