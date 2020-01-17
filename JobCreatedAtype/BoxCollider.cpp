//======================================================
// File Name	: BoxCollider.cpp
// Summary		: コライダー(Box)
// Date			: 2019/12/13
// Author		: Kazuaki Hashimoto
//======================================================
#include "pch.h"
#include "BoxCollider.h"
#include "SphereCollider.h"
#include "CollisionManager.h"

BoxCollider::BoxCollider(const DirectX::SimpleMath::Vector3& size)
	:m_size(size)
{
}


bool BoxCollider::IsCollided(const Collider * collider) const
{
	return collider->IsCollided(this);
}

bool BoxCollider::IsCollided(const SphereCollider * collider) const
{
	return collider->IsCollided(this);
}

bool BoxCollider::IsCollided(const BoxCollider * collider) const
{
	return CollisionManager::IsCollided(this, collider);
}


