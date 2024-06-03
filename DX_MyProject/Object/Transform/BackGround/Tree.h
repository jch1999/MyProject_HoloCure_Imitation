#pragma once
class Tree :public Transform
{
private:
	float spawn_rate;

	Transform* target;
	Vector2 offset;
	vector<Clip*> clips;
	int clip_idx;
	Vector2 render_size;

	VertexShader* VS;
	PixelShader* PS;
	ColourBuffer* CB;

	RectCollider* collider;
	Vector2 collider_offset;

	map<pair<int, int>, bool> active_record;
	map<pair<int, int>, int> clip_record;
public:
	Tree();
	~Tree();

	void Update();
	void Render();
	void PostRender();
	void SetIndex(int idx);
	void SetTarget(Transform* t) { target = t; }
	void SetOffset(Vector2 offset) { this->offset = offset; }
	void ChangePos();
	void SetColor(Float4 color) { CB->data.colour = color; }
	Collider* GetCollider() { return collider; }
};