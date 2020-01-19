//======================================================
// File Name	: FollowCamera.cpp
// Summary		: �J����
// Date			: 2019/05/31
// Author		: Kazuaki Hashimoto
//======================================================

#include "pch.h"
#include "FollowCamera.h"

#include <SimpleMath.h>
#include "DeviceResources.h"
#include "DebugFont.h"

#include "GameContext.h"
#include "CollisionManager.h"
#include "SphereCollider.h"
#include "Transform.h"

//�萔�̒�`
const DirectX::SimpleMath::Vector3 FollowCamera::TARGET_TO_EYE_VEC(0.0f, 5.0f, 10.0f);  //�J�����̋���
const float FollowCamera::TIME_TO_TURN = 0.3f;                                          //�ۊǂ��ĉ�鎞��
const float FollowCamera::TIME_TO_DELAY = 0.05f;                                        //�J������x�点�鎞��

// �R���X�g���N�^
FollowCamera::FollowCamera(DirectX::SimpleMath::Vector3 target)
	: m_target(target)
{
	RECT size = GameContext<DX::DeviceResources>::Get()->GetOutputSize();
	float aspectRatio = float(size.right) / float(size.bottom);

	// ��p��ݒ�
	float fovAngleY = DirectX::XMConvertToRadians(45.0f);

	// �v���W�F�N�V�����s��v�Z�E�ݒ�
	m_projection = DirectX::SimpleMath::Matrix::CreatePerspectiveFieldOfView(
		fovAngleY,
		aspectRatio,
		0.01f,
		10000.0f);
}
// �f�X�g���N�^
FollowCamera::~FollowCamera()
{

}

// �X�V
void FollowCamera::Update()
{
	// �J�����̊p�x�̐ݒ�
	DirectX::SimpleMath::Vector3 up(0.0f, 1.0f, 0.0f);

	// �S���R�Ǐ]
	m_target += (m_refTargetPos - m_target) * TIME_TO_DELAY;

	// Laap
	m_rotation = DirectX::SimpleMath::Quaternion::Slerp(m_rotation, m_refRotation, TIME_TO_TURN);

	// Eye�̍X�V
	m_eye = DirectX::SimpleMath::Vector3::Transform(TARGET_TO_EYE_VEC, m_rotation);

	// View�̌���
	m_view = DirectX::SimpleMath::Matrix::CreateLookAt(m_target + m_eye, m_target, up);
}

// �J�����̉�]
void FollowCamera::RotateCamera(const DirectX::SimpleMath::Quaternion& rotation, bool immediately)
{
	// ��]�̍X�V
	m_refRotation *= rotation;

	// true�Ȃ�Εۊǂ���߂�
	if (immediately)
		m_rotation = m_refRotation;
}
