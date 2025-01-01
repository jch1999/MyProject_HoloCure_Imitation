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

	clips.clear();
}


void Projectile::PostRender()
{
}

void Projectile::InitFrame()
{
}

void Projectile::ClearFrame()
{
}

void Projectile::SetStatus(float inDamage, float inSpeed, int inHitCount, float inLifeTime, float inHitCoolDown)
{
	this->damage = inDamage;
	this->speed = inSpeed;
	this->maxHitCount = inHitCount;
	this->nowHitCount = 0;
	this->lifeTime = inLifeTime;
	this->nowTime = 0.0f;
	this->hitCoolDown = inHitCoolDown;
}

void Projectile::SetDirection(Vector2 inDir)
{
	moveDir = inDir;
}


void Projectile::SetColliderIdx(int inIdx)
{
	colliders[colliderIdx]->SetActive(false);
	collider = colliders[inIdx];
	colliderIdx = inIdx;
	colliders[colliderIdx]->SetActive(true);
}

void Projectile::SetClipIdx(int inIdx)
{
	clipIdx = inIdx;
}

void Projectile::SetTargetDist(float inDist)
{
	targetDist = inDist;
}

void Projectile::SetLifeTime(float inTime)
{
	lifeTime = inTime;
}

void Projectile::SetCrt(bool inCrt)
{
	isCrt = inCrt;
}

void Projectile::SetCoolDown(float inTime)
{
	hitCoolDown = inTime;
}

void Projectile::SetHitLimit(int inCnt)
{
	hitLimitCnt = inCnt;
}

void Projectile::SetKnockBack(bool inKnockBack)
{
	isKnockback = inKnockBack;
}

void Projectile::SetOwner(Skill* inSkill)
{
	Owner = inSkill;
}