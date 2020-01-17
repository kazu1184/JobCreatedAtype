//======================================================
// File Name	: SphereCollider.cpp
// Summary		: コライダー(Sphere)
// Date			: 2019/12/13
// Author		: Kazuaki Hashimoto
//======================================================
#include "pch.h"
#include "SphereCollider.h"
#include "CollisionManager.h"

SphereCollider::SphereCollider(float radius)
	:m_radius(radius)
{
}

bool SphereCollider::IsCollided(const Collider * collider) const
{
	return collider->IsCollided(this);
}

bool SphereCollider::IsCollided(const SphereCollider * collider) const
{
	return CollisionManager::IsCollided(this, collider);
}

bool SphereCollider::IsCollided(const BoxCollider * collider) const
{
	return CollisionManager::IsCollided(this, collider);
}
