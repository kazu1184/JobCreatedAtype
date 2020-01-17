//======================================================
// File Name	: Transform.h
// Summary		: ポジション・ローテーション・スケール
// Date			: 2019/12/11
// Author		: Kazuaki Hashimoto
//======================================================
#include "pch.h"
#include "Transform.h"

Transform::Transform()
	: m_world(DirectX::SimpleMath::Matrix::Identity)
	, m_position(0.0f,0.0f,0.0f)
	, m_rotation(0.0f,0.0f,0.0f)
	, m_scale(1.0f,1.0f,1.0f)
{
}

Transform::~Transform()
{
}

void Transform::Initialize()
{
}

void Transform::Update()
{
	// スケール
	m_world = DirectX::SimpleMath::Matrix::CreateScale(m_scale);
	// 回転
	m_world *= DirectX::SimpleMath::Matrix::CreateRotationX(DirectX::XMConvertToRadians(m_rotation.x));
	m_world *= DirectX::SimpleMath::Matrix::CreateRotationY(DirectX::XMConvertToRadians(m_rotation.y));
	m_world *= DirectX::SimpleMath::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(m_rotation.z));
	// 移動
	m_world *= DirectX::SimpleMath::Matrix::CreateTranslation(m_position);
}
