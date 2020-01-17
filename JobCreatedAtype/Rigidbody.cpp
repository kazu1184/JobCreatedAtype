//======================================================
// File Name	: Rigidbody.cpp
// Summary		: ���W�b�g�{�f�B
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
	// �ő呬�x�ȏ�ɂȂ�Ȃ��悤����
	if (m_vel.LengthSquared() > maxSpeed * maxSpeed)
	{
		m_vel.Normalize();
		m_vel *= maxSpeed;
	}

	// �|�W�V�����Ƀx���V�e�B�𑫂�
	m_parentTransform->SetPosition(m_parentTransform->GetPosition() + m_vel);
}

void Rigidbody::AddForce(float angle, float force)
{
	// �i�s�����x�N�g��
	DirectX::SimpleMath::Vector3 dir(0.0f, 0.0f, -1.0f);

	// ���@�̌����x�N�g�������߂�
	DirectX::SimpleMath::Matrix rotY = DirectX::SimpleMath::Matrix::CreateRotationY(angle);
	dir = DirectX::SimpleMath::Vector3::Transform(dir, rotY);

	// �����x
	m_acc = dir * force;

	// ���x�ɉ����x�𑫂�
	m_vel += m_acc;
}

void Rigidbody::AddForce(DirectX::SimpleMath::Vector3 rotY, float force)
{
	// �����x
	m_acc = rotY * force;
	m_acc.y = 0.0f;

	// ���x�ɉ����x�𑫂�
	m_vel += m_acc;

}
