//======================================================
// File Name	: Collider.cpp
// Summary		: �R���C�_�[���N���X
// Date			: 2019/12/12
// Author		: Kazuaki Hashimoto
//======================================================
#include "pch.h"
#include "Collider.h"
#include "BoxCollider.h"
#include "SphereCollider.h"
#include "RayCollider.h"

Collider::Collider()
{
}

void Collider::OnCollision(Collider * object)
{
	GetParent()->OnCollision(object->GetParent());
}


