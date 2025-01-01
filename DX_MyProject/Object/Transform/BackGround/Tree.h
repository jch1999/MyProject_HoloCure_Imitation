#pragma once
class Tree :public BackgroundObject
{
protected:
	static vector<shared_ptr<const Frame>>& GetTreeFrames();
	static int& GetTreeUseCnt();

private:
	RectCollider* collider;
	Vector2 colliderOffset;

public:
	Tree(Vector2 inRenderSize = Vector2(137.0f, 133.0f) * 1.5f, float inSpawnRate = 0.85f);
	~Tree();

	virtual void Update() override;
	virtual void Render() override;
	
	virtual void InitFrame() override;
	virtual void ClearFrame() override;

	virtual void SetIndex(int idx) override;
	virtual void ChangePos() override;
	Collider* GetCollider() { return collider; }
};