//======================================================
// File Name	: FollowCamera.h
// Summary		: �J����
// Date			: 2019/05/31
// Author		: Kazuaki Hashimoto
//======================================================
#pragma once
#include "SimpleMath.h"

class RayCollider;

class FollowCamera 
{
	public: //�����o�萔

		//�J�����̋���
		static const DirectX::SimpleMath::Vector3 TARGET_TO_EYE_VEC;

	private: //�����o�萔

		//�ۊǂ��ĉ�鎞��
		static const float TIME_TO_TURN;
		//�J������x�点�鎞��
		static const float TIME_TO_DELAY;

	private: //�����o�ϐ�

		// �������ꂽ�r���[�s��
		DirectX::SimpleMath::Matrix m_view;
		// �v���W�F�N�V����
		DirectX::SimpleMath::Matrix m_projection;
		// �����_
		DirectX::SimpleMath::Vector3 m_target;
		DirectX::SimpleMath::Vector3 m_eye;
		// �Q�ƒ����_ 
		DirectX::SimpleMath::Vector3 m_refTargetPos;
		// ��]
		DirectX::SimpleMath::Quaternion m_rotation;
		// �ۊǗp��]
		DirectX::SimpleMath::Quaternion m_refRotation;
		// Ray
		RayCollider* m_ray;
	
	
	public: // �R���X�g���N�^�E�f�X�g���N�^
		
		FollowCamera(DirectX::SimpleMath::Vector3 target);
		~FollowCamera();
	
	public: //�����o�֐�

		void Update();
		void RotateCamera(const DirectX::SimpleMath::Quaternion& rotation, bool immediately = false);
	
	public: //�A�N�Z�b�T

		// �Q�ƒ����_
		DirectX::SimpleMath::Vector3 getRefTargetPos(){ return m_refTargetPos; }
		void setRefTargetPos(const DirectX::SimpleMath::Vector3& ref){ m_refTargetPos = ref; }
	
		DirectX::SimpleMath::Vector3 getEye() { return m_eye; }

		// �r���[�s��擾
		const DirectX::SimpleMath::Matrix& GetView(){ return m_view; }

		// �v���W�F�N�V�����s��擾
		const DirectX::SimpleMath::Matrix& GetProjection() { return m_projection; }
	
		// �ۊǗp��]�擾
		DirectX::SimpleMath::Quaternion GetRotation(){ return m_refRotation; }

		// ��]�Z�b�g
		void SetRotation(const DirectX::SimpleMath::Quaternion& angle,bool immediately = false)
		{
			m_refRotation = angle;

			if (immediately)
				m_rotation = m_refRotation;
		}
};