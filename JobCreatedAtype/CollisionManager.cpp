#include "pch.h"
#include "CollisionManager.h"
#include "SphereCollider.h"
#include "BoxCollider.h"
#include "RayCollider.h"
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

float CollisionManager::Clamp(float n, float min, float max)
{
	if (n < min) return min; if (n > max) return max; return n;
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

bool CollisionManager::IsCollided(const BoxCollider * collider1, const RayCollider * collider2)
{
	DirectX::SimpleMath::Vector3 vel = collider1->GetPosition() - collider2->GetStartRay();
	float length = vel.Length();
	if (fabs(length) > collider2->GetLength())
		return false;
	// 方向ベクトル正規化
 	DirectX::SimpleMath::Vector3 end = collider2->GetEndRay();
	end.Normalize();
	// 直線を境界ボックスの空間へ移動
	DirectX::SimpleMath::Matrix invMat = collider1->GetParent()->GetTransform()->GetWorld().Invert();
	DirectX::SimpleMath::Vector3 p_l, dir_l;
	p_l = DirectX::SimpleMath::Vector3::Transform(collider2->GetStartRay(), invMat);
	invMat._41 = 0.0f;
	invMat._42 = 0.0f;
	invMat._43 = 0.0f;
	dir_l = DirectX::SimpleMath::Vector3::Transform(end, invMat);
	// 交差判定
	float p[3], d[3], min[3], max[3];
	memcpy(p, &p_l, sizeof(DirectX::SimpleMath::Vector3));
	memcpy(d, &dir_l, sizeof(DirectX::SimpleMath::Vector3));

	min[0] = - collider1->GetSize().x;
	min[1] = - collider1->GetSize().y;
	min[2] = - collider1->GetSize().z;
	max[0] = + collider1->GetSize().x;
	max[1] = + collider1->GetSize().y;
	max[2] = + collider1->GetSize().z;

	float tmp_t = -FLT_MAX;
	float t_max = FLT_MAX;

	for (int i = 0; i < 3; ++i) 
	{
		if (abs(d[i]) < FLT_EPSILON) 
		{
			if (p[i] < min[i] || p[i] > max[i])
				return false; // 交差していない
		}
		else 
		{
			// スラブとの距離を算出
			// t1が近スラブ、t2が遠スラブとの距離
			float odd = 1.0f / d[i];
			float t1 = (min[i] - p[i]) * odd;
			float t2 = (max[i] - p[i]) * odd;

			if (t1 > t2) {
				float tmp = t1; t1 = t2; t2 = tmp;
			}
			if (t1 > tmp_t) tmp_t = t1;
			if (t2 < t_max) t_max = t2;
			// スラブ交差チェック
			if (tmp_t >= t_max)
				return false;
		}
	}

	//if (t)
	//{
	//	*t = tmp_t;
	//}
	// 交差している
	//if (colPos) {
	//	*colPos = nLine.start + tmp_t * nLine.end;
	//}
	return true;
}

bool CollisionManager::IsCollided(const RayCollider * collider1, const BoxCollider * collider2)
{
	return IsCollided(collider2, collider1);
}

bool CollisionManager::IsCollided(const SphereCollider * collider1, const RayCollider * collider2)
{
	// 球の中心とラインの開始地点と終了地点の計算
	float dist2 = SqDistPointSegment(collider2->GetStartRay(), collider2->GetStartRay() + collider2->GetEndRay(), collider1->GetPosition());
	float radius = collider1->GetRadius();

	return dist2 <= radius * radius;
}

bool CollisionManager::IsCollided(const RayCollider * collider1, const SphereCollider * collider2)
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

float CollisionManager::SqDistPointSegment(DirectX::SimpleMath::Vector3 a, DirectX::SimpleMath::Vector3 b, DirectX::SimpleMath::Vector3 c)
{
	DirectX::SimpleMath::Vector3 ab = b - a;
	DirectX::SimpleMath::Vector3 ac = c - a;
	DirectX::SimpleMath::Vector3 bc = c - b;

	float e = ac.Dot(ab);

	if (e <= 0.0f) 
		return ac.Dot(ac);

	float f = ab.Dot(ab);

	if (e >= f) 
		return bc.Dot(bc);

	return ac.Dot(ac) - e * e / f;
}

float CollisionManager::ClosestPtSegmentSegment(DirectX::SimpleMath::Vector3 p1, DirectX::SimpleMath::Vector3 q1, DirectX::SimpleMath::Vector3 p2, DirectX::SimpleMath::Vector3 q2, float & s, float & t, DirectX::SimpleMath::Vector3 & c1, DirectX::SimpleMath::Vector3 & c2)
{
	{
		DirectX::SimpleMath::Vector3 d1 = q1 - p1;
		DirectX::SimpleMath::Vector3 d2 = q2 - p2;
		DirectX::SimpleMath::Vector3 r = p1 - p2;
		float a = d1.Dot(d1);
		float e = d2.Dot(d2);
		float f = d2.Dot(r);

		if (a <= FLT_EPSILON && e <= FLT_EPSILON) {
			s = t = 0.0f;
			c1 = p1;
			c2 = p2;
			return (c1 - c2).Dot(c1 - c2);
		}
		if (a <= FLT_EPSILON) {
			s = 0.0f;
			t = f / e;
			t = Clamp(t, 0.0f, 1.0f);
		}
		else
		{
			float c = d1.Dot(r);
			if (e <= FLT_EPSILON)
			{
				t = 0.0f; s = Clamp(-c / a, 0.0f, 1.0f);
			}
			else {
				float b = d1.Dot(d2);
				float denom = a * e - b * b;
				if (denom != 0.0f)
				{
					s = Clamp((b * f - c * e) / denom, 0.0f, 1.0f);
				}
				else
				{
					s = 0.0f;
				}
				float tnom = (b * s + f);
				if (tnom < 0.0f)
				{
					t = 0.0f; s = Clamp(-c / a, 0.0f, 1.0f);
				}
				else if (tnom > e)
				{
					t = 1.0f;
					s = Clamp((b - c) / a, 0.0f, 1.0f);
				}
				else
				{
					t = tnom / e;
				}
			}
		}

		c1 = p1 + d1 * s;
		c2 = p2 + d2 * t;
		return (c1 - c2).Dot(c1 - c2);

	}
}
