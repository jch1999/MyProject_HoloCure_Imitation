#pragma once
class SunLight :public Transform
{
protected:
	static vector<shared_ptr<const Frame>> SunLightFrames;
	static int SunLightUseCnt;

private:
	Transform* target;
	Vector2 offset;
	vector<shared_ptr<Clip>> clips;
	int clip_idx;
	Vector2 render_size;

	VertexShader* VS;
	PixelShader* PS;
	ColourBuffer* CB;

public:
	SunLight();
	~SunLight();

	void Init();
	void Update();
	void Render();
	void PostRender();
	void SetIndex(int idx);
	void SetTarget(Transform* t) { target = t; }
	void SetOffset(Vector2 offset) { this->offset = offset; }

protected:
	FORCEINLINE static shared_ptr<const Frame> GetSunLightFrame(int idx) { return SunLightFrames[idx]; }

};