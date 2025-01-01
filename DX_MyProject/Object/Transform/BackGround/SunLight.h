#pragma once
class SunLight :public BackgroundObject
{
protected:
	static vector<shared_ptr<const Frame>>& GetSunLightFrames();
	static int& GetSunLightUseCnt();

public:
	SunLight(Vector2 inRenderSize = Vector2(WIN_WIDTH, WIN_HEIGHT));
	~SunLight();

	virtual void Update() override;
	virtual void Render() override;
	virtual void InitFrame() override;
	virtual void ClearFrame() override;
	virtual void SetIndex(int inIdx) override;
};