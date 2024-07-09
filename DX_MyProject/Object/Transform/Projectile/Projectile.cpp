#include "framework.h"

Projectile::Projectile(float damage, float speed, int maxHitCount, float lifeTime)
	:damage(damage),speed(speed), maxHitCount(maxHitCount),lifeTime(lifeTime),nowTime(0.0f)
{
	VS = VertexShader::GetInstance(L"Shader/VertexShader/VertexUV.hlsl", 1);
	PS = PixelShader::GetInstance(L"Shader/PixelShader/PixelUV.hlsl");
	CB = new ColourBuffer();
}

Projectile::~Projectile()
{
	delete CB;

	for (auto c : colliders)
		delete c;

	for (auto c : clips)
		delete c;
}

void Projectile::SetStatus(float damage, float speed, int hitCount, float lifeTime)
{
	this->damage = damage;
	this->speed = speed;
	this->maxHitCount = hitCount;
	this->nowHitCount = 0;
	this->lifeTime = lifeTime;
	this->nowTime = 0.0f;
}


void Projectile::SetColliderIdx(int idx)
{
	colliders[idx_collider]->SetActive(false);
	collider = colliders[idx];	
	idx_collider = idx;
	colliders[idx_collider]->SetActive(true);
}
