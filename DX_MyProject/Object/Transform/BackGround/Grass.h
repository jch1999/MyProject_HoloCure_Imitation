#pragma once
class Grass:public Transform
{
protected:
	static vector<shared_ptr<const Frame>> grassFrames;
	static int grassUseCnt;

private:
	float spawn_rate;

	Transform* target;
	Vector2 offset;
	shared_ptr<const Frame> frame;
	int frameIdx;
	Vector2 renderSize;

	VertexShader* VS;
	PixelShader* PS;
	ColourBuffer* CB;

	map<pair<int, int>, bool> activeRecord;
	map<pair<int, int>, int> clipRecord;
public:
	Grass();
	~Grass();

	void Init();
	void Update();
	void Render();
	void PostRender();
	void SetIndex(int idx);
	void SetTarget(Transform* t) { target = t; }
	void SetOffset(Vector2 offset) { this->offset = offset; }
	void ChangePos();
};