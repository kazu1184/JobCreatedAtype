//======================================================
// File Name	: Player.h
// Summary		: Player�N���X
// Date			: 2019/12/24
// Author		: Kazuaki Hashimoto
//======================================================
#pragma once
#include "GameObject.h"

#include <Model.h>
#include <Keyboard.h>

class RayCollider;

class CharacterState;
class StandState;
class MoveState;
class MapPosition;
class KnockBackState;

class Player : public GameObject
{
	public:
		// �ړ����
		enum DIRECTION
		{
			NONE,
			FORWARD,
			BACKWARD
		};
		// �萔
		static const float CAMERA_DIRECTION;
		static const float INITIALIZE_ANGLE;

	private:
		// �v���C���[���f��
		std::unique_ptr<DirectX::Model> m_playerModel;
		// �J�����ƃv���C���[�̌����Ă���p�x
		float m_angle;
		// �}�b�v�|�W�V����
		MapPosition* m_playerMapPos;
		// �ړ��̃X�e�C�g
		DIRECTION m_direction;
		// ���݂̏��
		CharacterState* m_currentState;
		// ���[�u���
		std::unique_ptr<MoveState> m_moveState;
		// �Î~���
		std::unique_ptr<StandState> m_standState;
		// �m�b�N�o�b�N
		std::unique_ptr<KnockBackState> m_knockBackState;
		// �L�[�{�[�h�g���b�J�[
		std::unique_ptr<DirectX::Keyboard::KeyboardStateTracker> m_keyboardTracker;
		
	public:
		// �R���X�g���N�^�E�f�X�g���N�^
		Player();
		~Player();

		void Update()override;
		void Render()override;
		// �����蔻��
		void OnCollision(GameObject* object)override;

		// ���݂̏�Ԃ��擾
		CharacterState* GetCurrentState() { return m_currentState; }
		// Stand��Ԃ��擾
		StandState* GetStand() { return m_standState.get(); }
		// Move��Ԃ��擾
		MoveState* GetMove() { return m_moveState.get(); }
		// �m�b�N�o�b�N��Ԃ��擾
		KnockBackState* GetKnockBack() { return m_knockBackState.get(); }

		// �����̎擾
		DIRECTION GetDirection() { return m_direction; }
		// �����̃Z�b�g
		void SetDirection(DIRECTION dir) { m_direction = dir; }

		float GetAngle() { return m_angle; }

		MapPosition* GetMapPosition() { return m_playerMapPos; }

		// ��ԑJ��
		void ChangeState(CharacterState* state)
		{
			m_currentState = state;
		}

	private:
		void CameraOperation(DirectX::Keyboard::State key);
};

