#include "framework.h"

PoisonArea::PoisonArea(Vector2 size)
	:Projectile(20.0f, 200.0f, 1, 2.0f)
{
	wstring file = L"Textures/Skill/PC Computer - HoloCure - Save the Fans - Weapons_rm_bg.png";
	Texture* t = Texture::Add(file);

	this->size = size;
	vector<Frame*> frames;

	// PROJ_STATE::NORMAL
	frames.push_back(new Frame(file, 4.0f, 80.0f, 107.0f, 107.0f));
	clips.push_back(new Clip(frames, Clip::CLIP_TYPE::END, 1.0f));
	frames.clear();

	// 0~2 : SpiderCooking��ų�� �⺻ collider ����,
	colliders.push_back(new CircleCollider(size.x * 0.5f));
	colliders.push_back(new CircleCollider(size.x * 0.5f * 1.15f)); // SpiderCooking LV 2
	colliders.push_back(new CircleCollider(size.x * 0.5f * 1.25f)); // SpiderCooking LV 4

	idx_collider=0;
	collider = colliders[idx_collider];
	collider->pos = pos;
	CB->data.colour = Float4(1.0f, 1.0f, 1.0f, 0.5f);
}

PoisonArea::~PoisonArea()
{
}

void PoisonArea::Update()
{
	if (!is_active)return;

	WorldUpdate();

	collider->pos = pos;
	collider->WorldUpdate();

	scale = clips[clip_idx]->GetFrameSize() * collider->Size() /
		clips[clip_idx]->GetFrameOriginSize();

	clips[clip_idx]->Update();
}

void PoisonArea::Render()
{
	if (!is_active)return;

	VS->Set();
	PS->Set();

	WB->SetVS(0);
	CB->SetPS(0);

	clips[clip_idx]->Render();
	collider->Render();
}

void PoisonArea::PostRender()
{
}

void PoisonArea::respwan()
{
	// �� �� Ȱ��ȭ�Ǹ� ��Ȱ���� ���� ����
	return;
}

void PoisonArea::OnCollision()
{
	// �浹 ���� Enemey ����
	enemyNowFrame.clear();
	removeList.clear();
	//const vector<Enemy*>& enemyList = EnemySpawner::Get()->GetEnemyList();
	// Slash�� pos�� CELL ��ġ�� �߾����� 3x3 ������ �˻�
	// EnemySpawner���� ��� cell�� �������� 3x3 ũ�⿡ ���ԵǴ� ���� ������ �����ߴµ� ���⼭
	// �� 3x3���� �˻��ϸ� 9�� ������?
	pair<int, int> sPos = make_pair(pos.x / CELL_X, pos.y / CELL_Y);
	list<Enemy*> enemyList = EnemySpawner::Get()->GetPartition(make_pair(sPos.first, sPos.second));
	for (auto e : enemyList)
	{
		if (!e->is_active)continue;
		// �ݶ��̴� ���� ������ �Ÿ� < �ݶ��̴� ������ �� �� ���� �浹 �˻�
		float sumLength = GetCollider()->Size().GetLength() + e->GetDamageCollider()->Size().GetLength();
		float dist = (GetCollider()->pos - e->GetDamageCollider()->pos).GetLength();
		if (sumLength >= dist)
		{
			if (GetCollider()->isCollision(e->GetDamageCollider()))
				enemyNowFrame.push_back(e);
		}
	}

	// ���Ӱ� �߰��� ���ʹ� �߰�
	for (auto e : enemyNowFrame)
	{
		// ������ �������� ���� - �߰� �� �ٷ� �����ϰ� ����
		if (hitEnemies.find(e) == hitEnemies.end())
		{
			hitEnemies.insert(e);
			cooltimeList.push_back(make_pair(e, 0.0f));
		}
	}

	// �ð� ��� üũ, coolTime�� �������� damage�ֱ�
	list<pair<Enemy*, float>>::iterator iter = cooltimeList.begin();
	for(; iter != cooltimeList.end();iter++)
	{
		(*iter).second -= DELTA;
		if ((*iter).second <= 0.0f)
		{
			// ���� �浹 ���̶��
			if (find(enemyNowFrame.begin(), enemyNowFrame.end(), (*iter).first) != enemyNowFrame.end())
			{
				(*iter).second = hitCoolDown;

				damage = dynamic_cast<SpiderCooking*>(SkillManager::Get()->GetSkillByID(Skill::SKILL_ID::SPIDER_COOKING))->GetDamage();
				if (SkillManager::Get()->GetPlayer()->isCritical())
				{
					(*iter).first->ChangeHP(-damage * 1.5f, true);
				}
				else
				{
					(*iter).first->ChangeHP(-damage, false);
				}
				if (isKnockback)
					(*iter).first->SetKnockBack((*iter).first->GetMoveDir() * -1.0f, 300.0f, 0.13f);

				// �̹� ���� Enemy�� ���� ����Ʈ�� �߰�
				if (!(*iter).first->is_active)
				{
					removeCooltimeList.push_back((*iter));
				}
			}
			else // �浹���� ���� ���·� �浹 ���ð��� �����ٸ� ����
			{
				removeCooltimeList.push_back((*iter));
			}
		}
	}

	// ����
	for (auto e : removeCooltimeList)
	{
		cooltimeList.remove(e);
	}
}

void PoisonArea::Hit()
{
	// �浹 Ƚ�� ���� ����
	return;
}