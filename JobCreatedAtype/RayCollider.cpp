#include "pch.h"
#include "RayCollider.h"
#include "BoxCollider.h"
#include "SphereCollider.h"
#include "CollisionManager.h"


RayCollider::RayCollider()
{
}


bool RayCollider::IsCollided(const Collider * collider) const
{
	return collider->IsCollided(this);
}

bool RayCollider::IsCollided(const SphereCollider * collider) const
{
	return collider->IsCollided(this);
}

bool RayCollider::IsCollided(const BoxCollider * collider) const
{
	return collider->IsCollided(this);
}

bool RayCollider::IsCollided(const RayCollider * collider) const
{
	return false;
}

