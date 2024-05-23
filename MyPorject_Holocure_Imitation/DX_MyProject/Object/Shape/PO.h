#pragma once

class PO : public Transform
{
public:
    enum class PO_TYPE
    {
        PLAYER,
        ENEMY
    };
protected:
    Quad* image;
    Collider* collider;

    Vector2 size;
    PO_TYPE type;
    float speed;

public:
    PO(PO_TYPE type, Vector2 pos=Vector2(0,0), Vector2 size=Vector2(0,0), Vector2 scale=Vector2(1,1), float angle=0.f, Matrix* parent=NULL, float speed=15.0f);
    virtual ~PO();

    Vector2 Size() { return image!=nullptr?image->Size():Vector2(0,0); }

    void CreateImage(wstring file, Vector2 scale = Vector2(1, 1),
        Vector2 startUV = Vector2(0, 0), Vector2 EndUV = Vector2(1, 1));

    void CreateCollider(Collider::TYPE type, Vector2 pos, Vector2 size,float angle, Matrix* parent);
    void SetCollider(Collider* collider);
    Collider* GetCollider() { return collider; }

    void SetActive(bool activate);

    virtual void Update();
    virtual void Render();
};