//======================================================
// File Name	: BoxCollider.cpp
// Summary		: �R���C�_�[(Box)
// Date			: 2019/12/13
// Author		: Kazuaki Hashimoto
//======================================================
#include "pch.h"
#include "BoxCollider.h"
#include "SphereCollider.h"
#include "CollisionManager.h"
#include "RayCollider.h"
#include "GameContext.h"
#include "DeviceResources.h"
#include "FollowCamera.h"
#include "GameObjectManager.h"

BoxCollider::BoxCollider(const DirectX::SimpleMath::Vector3& size)
	:m_size(size)
{
}


void BoxCollider::Render()
{
	//// �J�����̍X�V
	//FollowCamera* camera = GameContext<GameObjectManager>::Get()->GetCamera();
	//// �W�I���g���̍쐬
	//m_debug = DirectX::GeometricPrimitive::CreateBox(GameContext<DX::DeviceResources>::Get()->GetD3DDeviceContext(), m_size);
	//// �`��
	//DirectX::SimpleMath::Matrix world = GetParent()->GetTransform()->GetWorld();
	//m_debug->Draw(world, camera->GetView(), camera->GetProjection(), DirectX::Colors::Green);
}

bool BoxCollider::IsCollided(const Collider * collider) const
{
	return collider->IsCollided(this);
}

bool BoxCollider::IsCollided(const SphereCollider * collider) const
{
	return CollisionManager::IsCollided(this, collider);
}

bool BoxCollider::IsCollided(const BoxCollider * collider) const
{
	return CollisionManager::IsCollided(this, collider);
}

bool BoxCollider::IsCollided(const RayCollider * collider) const
{
	return CollisionManager::IsCollided(this, collider);
}


