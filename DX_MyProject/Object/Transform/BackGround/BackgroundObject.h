#pragma once
class BackgroundObject:public Transform
{
protected:
	float spawnRate;

	Transform* target;
	Vector2 offset;
	int frameIdx;
	int frameMaxIdx;

	Vector2 renderSize;

	VertexShader* VS;
	PixelShader* PS;
	ColourBuffer* CB;

	map<pair<int, int>, bool> activeRecord;
	map<pair<int, int>, int> frameRecord;

public:
	BackgroundObject(Vector2 inRenderSize = Vector2(0.0f, 0.0f), float inSpawnRate = 0.0f, int inFrameMaxIdx = 0);
	~BackgroundObject();

	virtual void Update()=0;
	virtual void Render();
	virtual void PostRender();

	virtual void SetIndex(int inIdx);
	FORCEINLINE const int& GetIndex() { return frameIdx; }
	virtual void SetMaxIdx(int inIdx);
	FORCEINLINE const int& GetMaxIdx() { return frameMaxIdx; }
	virtual void SetTarget(Transform* t);
	FORCEINLINE const Transform* GetTarget() { return target; }
	virtual void SetOffset(Vector2 offset);
	FORCEINLINE const Vector2& GetOffset() { return offset; }
	virtual void SetColor(Float4 inColor);
	FORCEINLINE const Float4 GetColor() { return CB->data.colour; }

	virtual void ChangePos();
	virtual void InitFrame();
	virtual void ClearFrame();
};