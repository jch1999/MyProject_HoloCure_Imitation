#pragma once
class Flower :public Transform
{
protected:
	static vector<shared_ptr<const Frame>> flowerFrames;
	static int flowerUseCnt;

private:
	float spawn_rate;

	Transform* target;
	Vector2 offset;
	vector<shared_ptr<const Clip>> clips;
	int clipIdx;
	Vector2 renderSize;

	VertexShader* VS;
	PixelShader* PS;
	ColourBuffer* CB;

	map<pair<int, int>, bool> activeRecord;
	map<pair<int, int>, int> clipRecord;
public:
	Flower();
	~Flower();

	void Update();
	void Render();
	void PostRender();
	void SetIndex(int idx);
	void SetTarget(Transform* t) { target = t; }
	void SetOffset(Vector2 offset) { this->offset = offset; }
	void ChangePos();
	void SetColor(Float4 color) { CB->data.colour = color; }
	void InitFrame();
	void ClearFrame();
};