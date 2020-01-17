//======================================================
// File Name	: Rigidbody.cpp
// Summary		: リジットボディ
// Date			: 2019/01/08
// Author		: Kazuaki Hashimoto
//======================================================
#include "pch.h"
#include "Rigidbody.h"

#include "Transform.h"
#include "GameObject.h"

Rigidbody::Rigidbody()
	: maxSpeed(1.0f)
{
}


Rigidbody::~Rigidbody()
{
}

void Rigidbody::Initialize()
{
	m_parentTransform = GetParent()->GetComponent<Transform>();
}

void Rigidbody::Update()
{
	// 最大速度以上にならないよう調整
	if (m_vel.LengthSquared() > maxSpeed * maxSpeed)
	{
		m_vel.Normalize();
		m_vel *= maxSpeed;
	}

	// ポジションにベロシティを足す
	m_parentTransform->SetPosition(m_parentTransform->GetPosition() + m_vel);
}

void Rigidbody::AddForce(float angle, float force)
{
	// 進行方向ベクトル
	DirectX::SimpleMath::Vector3 dir(0.0f, 0.0f, -1.0f);

	// 自機の向きベクトルを求める
	DirectX::SimpleMath::Matrix rotY = DirectX::SimpleMath::Matrix::CreateRotationY(angle);
	dir = DirectX::SimpleMath::Vector3::Transform(dir, rotY);

	// 加速度
	m_acc = dir * force;

	// 速度に加速度を足す
	m_vel += m_acc;
}

void Rigidbody::AddForce(DirectX::SimpleMath::Vector3 rotY, float force)
{
	// 加速度
	m_acc = rotY * force;
	m_acc.y = 0.0f;

	// 速度に加速度を足す
	m_vel += m_acc;

}
