#pragma once
class Tree :public Transform
{
protected:
	static vector<shared_ptr<const Frame>> treeFrames;
	static int TreeUseCnt;

private:
	float spawnRate;

	Transform* target;
	Vector2 offset;
	
	shared_ptr<const Frame> frame;
	int frameIdx;
	Vector2 renderSize;

	VertexShader* VS;
	PixelShader* PS;
	ColourBuffer* CB;

	RectCollider* collider;
	Vector2 colliderOffset;

	map<pair<int, int>, bool> activeRecord;
	map<pair<int, int>, int> frameRecord;
public:
	Tree();
	~Tree();

	void Update();
	void Render();
	void PostRender();
	
	void InitFrame();
	void ClearFrame();

	void SetIndex(int idx);
	void SetTarget(Transform* t) { target = t; }
	void SetOffset(Vector2 offset) { this->offset = offset; }
	void ChangePos();
	void SetColor(Float4 color) { CB->data.colour = color; }
	Collider* GetCollider() { return collider; }
};