#include "pch.h"
#include "CollisionManager.h"
#include "SphereCollider.h"
#include "BoxCollider.h"
#include "GameObject.h"
#include "Transform.h"


CollisionManager::CollisionManager()
{

}

CollisionManager::~CollisionManager()
{

}

void CollisionManager::Add(const std::string & groupName, Collider * collider)
{
	m_colliderGroups[groupName].push_back(collider);
}

void CollisionManager::AllowCollision(const std::string & groupName1, const std::string & groupName2)
{
	// 同じグループなら
	if (groupName1 == groupName2)
	{
		// 2つ目の要素はエンプティ
		m_collisionGroups.push_back(std::make_pair(groupName1, ""));
	}
	else
	{
		m_collisionGroups.push_back(std::make_pair(groupName1, groupName2));
	}
}

void CollisionManager::DetectCollision()
{
	for (const CollisionGroup& collisionGroup : m_collisionGroups)
	{
		// 2種類目がなければ
		if (collisionGroup.second.empty())
		{
			ColliderList& colliders = m_colliderGroups[collisionGroup.first];

			DetectCollision(colliders);
		}
		else
		{
			ColliderList& colliders1 = m_colliderGroups[collisionGroup.first];
			ColliderList& colliders2 = m_colliderGroups[collisionGroup.second];

			DetectCollision(colliders1, colliders2);
		}
	}

	//m_colliderGroups.clear();
}

void CollisionManager::DetectCollision(const ColliderList & colliders)
{
	// サイズの取得
	int numObjects = colliders.size();

	for (int i = 0; i < numObjects - 1; i++)
	{
		for (int j = i + 1; j < numObjects; j++)
		{
			if (colliders[i]->IsCollided(colliders[j]))
			{
				colliders[i]->OnCollision(colliders[j]);
				colliders[j]->OnCollision(colliders[i]);
			}
		}
	}
}

void CollisionManager::DetectCollision(const ColliderList & colliders1, const ColliderList & colliders2)
{
	for (Collider* collider1 : colliders1)
	{
		for (Collider* collider2 : colliders2)
		{
			if (collider1->IsCollided(collider2))
			{
				collider1->OnCollision(collider2);
				collider2->OnCollision(collider1);
			}
		}
	}
}

bool CollisionManager::IsCollided(const SphereCollider * collider1, const SphereCollider * collider2)
{
	// 中心間の距離の平方を計算
	DirectX::SimpleMath::Vector3 d = (collider1->GetPosition() - collider2->GetPosition());
	float dist2 = d.Dot(d);
	// 平方した距離が平方した半径の合計よりも小さい場合に球は交差している
	float radiusSum = collider1->GetRadius()/2 + collider2->GetRadius()/2;
	return dist2 <= radiusSum * radiusSum;
}

bool CollisionManager::IsCollided(const BoxCollider * collider1, const BoxCollider * collider2)
{
	if (abs(collider2->GetPosition().x - collider1->GetPosition().x) > collider1->GetSize().x/2 + collider2->GetSize().x/2)return false;
	if (abs(collider2->GetPosition().y - collider1->GetPosition().y) > collider1->GetSize().y/2 + collider2->GetSize().y/2)return false;
	if (abs(collider2->GetPosition().z - collider1->GetPosition().z) > collider1->GetSize().z/2 + collider2->GetSize().z/2)return false;
	return true;
}

bool CollisionManager::IsCollided(const SphereCollider * collider1, const BoxCollider * collider2)
{
	float sqDist = SqDistPointBox(collider1->GetPosition(), collider2);
	return sqDist <= collider1->GetRadius()/2 * collider1->GetRadius()/2;
}

bool CollisionManager::IsCollided(const BoxCollider * collider1, const SphereCollider * collider2)
{
	return IsCollided(collider2, collider1);
}

float CollisionManager::SqDistPointBox(const DirectX::SimpleMath::Vector3& p, const BoxCollider * b)
{
	float point[3] = { p.x, p.y, p.z };
	float min[3] = { b->GetPosition().x - b->GetSize().x/2, b->GetPosition().y - b->GetSize().y/2, b->GetPosition().z - b->GetSize().z/2 };
	float max[3] = { b->GetPosition().x + b->GetSize().x/2, b->GetPosition().y + b->GetSize().y/2, b->GetPosition().z + b->GetSize().z/2 };

	float sqDist = 0.0f;
	for (int i = 0; i < 3; i++)
	{
		float v = point[i];
		if (v < min[i]) sqDist += (min[i] - v) * (min[i] - v);
		if (v > max[i]) sqDist += (v - max[i]) * (v - max[i]);
	}
	return sqDist;
}
