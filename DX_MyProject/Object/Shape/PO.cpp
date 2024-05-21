#include "framework.h"


PO::PO(PO_TYPE type, Vector2 pos, Vector2 size, Vector2 scale, float angle, Matrix* parent, 
	 float speed)
	:Transform(pos,scale,angle,parent)
	,size(size)
	,type(type)
	,speed(speed)
	,collider(nullptr)
	,image(nullptr)
{
	//switch (type)
	//{
	//	case PO::PO_TYPE::PLAYER:
	//	{
	//		CreateImage(L"Textures/Images/knight_walk_1.png");
	//		CreateCollider(Collider::TYPE::RECT, Vector2(0,0),size,rot.z,this->GetWorld());
	//	}
	//	break;
	//	case PO::PO_TYPE::ENEMY:
	//	{
	//		CreateImage(L"Textures/Images/arrow.png");
	//		CreateCollider(Collider::TYPE::RECT, Vector2(0, 0), size, rot.z, this->GetWorld());
	//		//image->SetAngle(rot.z+45);
	//	}
	//default:
	//	break;
	//}
}

PO::~PO()
{
	delete image;

	delete collider;
}

void PO::CreateImage(wstring file, Vector2 scale, Vector2 startUV, Vector2 EndUV)
{
	image = new Quad(file.c_str(),scale,startUV,EndUV);
	image->SetParent(this->GetWorld());
}

void PO::CreateCollider(Collider::TYPE type, Vector2 pos, Vector2 size, float angle, Matrix* parent)
{
	switch (type)
	{
		case Collider::TYPE::RECT:
		{
			collider = new RectCollider(size);
		}
			break;
		case Collider::TYPE::CIRCLE:
		{
			collider = new CircleCollider(size.x);
		}
			break;
		default:
			break;
	}
	collider->pos = pos;
	collider->SetAngle(angle);
	collider->SetParent(parent);
}

void PO::SetCollider(Collider* col)
{
	delete collider;
	
	switch (col->GetType())
	{
		case Collider::TYPE::RECT:
		{
			collider = new RectCollider(((RectCollider*)col)->Size() / col->GlobalScale());
			CreateCollider(Collider::TYPE::RECT, Vector2(0, 0), ((RectCollider*)col)->Size() / col->GlobalScale(), rot.z, this->GetWorld());
		}
		break;
		case Collider::TYPE::CIRCLE:
		{
			collider = new CircleCollider(((CircleCollider*)col)->GetRadius());
			CreateCollider(Collider::TYPE::CIRCLE, Vector2(0, 0), Vector2(((CircleCollider*)col)->GetRadius(),0.0f), rot.z, this->GetWorld());
		}
		break;
		default:
			break;
	}
}

void PO::SetActive(bool activate)
{
	this->is_active = activate;
	
	if(image!=nullptr)
		image->is_active = activate;
	if(collider!=nullptr)
		collider->is_active = activate;
}

void PO::Update()
{
	if (!is_active)return;

	// 이동 처리
	/*if (KEY_CON->Press('W'))
	{
		this->pos.y -= speed * DELTA;
	}
	if (KEY_CON->Press('S'))
	{
		this->pos.y += speed * DELTA;
	}
	if (KEY_CON->Press('A'))
	{
		this->pos.x -= speed * DELTA;
	}
	if (KEY_CON->Press('D'))
	{
		this->pos.x += speed * DELTA;
	}*/
	this->WorldUpdate();

	if(image!=nullptr)
		image->WorldUpdate();
	if(collider!=nullptr)
		collider->WorldUpdate();
}

void PO::Render()
{
	if (!is_active)return;

	if(image!=nullptr)
		image->Render();
	if(collider!=nullptr)
		collider->Render();
}
