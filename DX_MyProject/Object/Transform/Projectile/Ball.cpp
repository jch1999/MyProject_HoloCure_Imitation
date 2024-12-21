#include "framework.h"

shared_ptr<const Frame> Ball::ballFrame;
int Ball::ballUseCnt=0;

Ball::Ball(ProjectileSize projSize)
	:Projectile(projSize)
{
	if (ballFrame == nullptr)
	{
		Init();
	}

	frame = ballFrame;
	
	colliders.push_back(new CircleCollider(size.x));
	collider = colliders[0];

	is_active = false;
	collider->SetActive(false);

	++ballUseCnt;
}

Ball::~Ball()
{
	if ((--ballUseCnt) == 0)
	{
		ballFrame.reset();
	}
}

void Ball::Init()
{
	if (ballFrame) return;

	wstring file = L"Textures/Skill/PC Computer - HoloCure - Save the Fans - Weapons_rm_bg.png";

	ballFrame=make_shared<const Frame>(file, 4.0f, 3425.0f, 41.0f, 41.0f);
}

void Ball::Update()
{
	if (nowTime >= lifeTime)
	{
		is_active = false;
	}

	nowTime += DELTA;
	velocity += Vector2(0, GRAVITY) * DELTA;
	pos = pos + velocity * speed * DELTA;
	WorldUpdate();

	collider->pos = pos;
	collider->WorldUpdate();

	if (nowCoolDown >= hitCoolDown)
	{
		OnCollision();
	}
	else
	{
		nowCoolDown += DELTA;
	}
}

void Ball::Render()
{
	if (!is_active)return;

	rot.z += velocity.x * DELTA;
	VS->Set();
	PS->Set();

	WB->SetVS(0);
	CB->SetPS(0);

	frame->Render();
	collider->Render();
}

void Ball::PostRender()
{
}

void Ball::respwan()
{
	nowTime = 0.0f;
	nowHitCount = 0;
	nowCoolDown = 0.0f;

	WorldUpdate();
	collider->pos = pos;
	collider->WorldUpdate();

	scale = frame->GetFrameSize() * collider->Size() /
		frame->GetFrameOriginSize();

	SetVelocity(Vector2(0.0f, 0.0f));

	is_active = true;
	collider->SetActive(true);
}

void Ball::Hit()
{
	/*nowHitCount++;

	if (nowHitCount == maxHitCount)
	{
		is_active = false;
		nowHitCount = 0;
		return;
	}*/

}

void Ball::AddVelocity(Vector2 newVel)
{
}

void Ball::OnCollision()
{
	// 충돌 검사
	pair<int, int> bPos = make_pair(pos.x / CELL_X, pos.y / CELL_Y);
	const list<Enemy*>& enemyList = EnemySpawner::Get()->GetPartition(bPos);
	for (auto e : enemyList)
	{
		float colDist = e->GetDamageCollider()->Size().GetLength() + GetCollider()->Size().x;
		if (colDist >= (pos - e->pos).GetLength())
		{
			if (GetCollider()->isCollision(e->GetDamageCollider()))
			{
				if (SkillManager::Get()->GetPlayer()->isCritical())
					e->ChangeHP(-(GetDamage() * 1.5f), true);
				else
					e->ChangeHP(-(GetDamage()), false);
				Hit();
				nowCoolDown = 0.0f;;

				// 넉백 주기
				if (isKnockback)
				{
					Vector2 dir = (GetVelocity().Normalized());
					e->SetKnockBack(dir, 300.0f, 0.08f);
				}

				// 튕겨내기
				Vector2 vel = GetVelocity();
				Vector2 colPos = e->GetDamageCollider()->pos;
				Vector2 colSize = e->GetDamageCollider()->Size();
				if (pos.x < e->pos.x && vel.x > 0.0f)
					vel.x *= -1.0f;
				else if (pos.x > e->pos.x && vel.x < 0.0f)
					vel.x *= -1.0f;
				else if (vel.x == 0.0f)
					vel.x += e->GetMoveDir().x * e->GetSpd();

				if (pos.y < e->pos.y && vel.y>0.0f)
					vel.y *= -1.0f;
				else if (pos.y > e->pos.y && vel.y < 0.0f)
					vel.y *= -1.0f;
				vel.y *= 0.6f;
				SetVelocity(vel);

				// 충돌에서 벗어나게 밀어내기
				//projectiles[i]->pos += (projectiles[i]->pos - e->GetDamageCollider()->pos).Normalized() * (colDist - (projectiles[i]->pos - e->pos).GetLength());
			}
		}
	}
}
