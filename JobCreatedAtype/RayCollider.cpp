#include "pch.h"
#include "RayCollider.h"
#include "BoxCollider.h"
#include "SphereCollider.h"
#include "CollisionManager.h"
// Debug
#include "GameContext.h"
#include "DeviceResources.h"
#include "DebugFont.h"
#include "GameObject.h"
#include "GameObjectManager.h"


RayCollider::RayCollider()
	: m_checkLength(0.0f)
{
}

void RayCollider::Render()
{
	//DebugFont* debug = DebugFont::GetInstance();
	//debug->print(10, 10, L"X :  %f", m_rayEnd.x);
	//debug->draw();
	//debug->print(10, 30, L"Y :  %f", m_rayEnd.y);
	//debug->draw();
	//debug->print(10, 50, L"Z :  %f", m_rayEnd.z);
	//debug->draw();

	//DirectX::SimpleMath::Vector3 pRay = GameContext<GameObjectManager>::Get()->Find("Player")[0]->GetTransform()->GetPosition();
	//m_pLinePrimitiveBatch->Begin();
	//DirectX::VertexPositionColor a, b;
	////a.position = m_rayStart;
	////b.position = m_rayEnd;
	//a.position = pRay;
	//b.position = pRay + DirectX::SimpleMath::Vector3(1,1,1);
	//a.color = b.color = DirectX::SimpleMath::Vector4::Zero;

	//m_pLinePrimitiveBatch->DrawLine(a, b);

	//m_pLinePrimitiveBatch->End();
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

