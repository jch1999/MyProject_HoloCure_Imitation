#include "framework.h"

Projectile::Projectile(ProjectileSize projSize, float damage, float speed, int maxHitCount, float lifeTime,float hitCooldown)
	:damage(damage),speed(speed), maxHitCount(maxHitCount),lifeTime(lifeTime),nowTime(0.0f),hitCoolDown(hitCooldown)
	,Owner(nullptr),collider(nullptr)
{
	this->size = projSize.GetSize();

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

void Projectile::SetStatus(float damage, float speed, int hitCount, float lifeTime, float hitCoolDown)
{
	this->damage = damage;
	this->speed = speed;
	this->maxHitCount = hitCount;
	this->nowHitCount = 0;
	this->lifeTime = lifeTime;
	this->nowTime = 0.0f;
	this->hitCoolDown = hitCoolDown;
}


void Projectile::SetColliderIdx(int idx)
{
	colliders[idx_collider]->SetActive(false);
	collider = colliders[idx];	
	idx_collider = idx;
	colliders[idx_collider]->SetActive(true);
}