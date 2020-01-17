#pragma once
#include "GameObject.h"

#include <Model.h>

class CharacterState;
class MapPosition;
class Player;

class Enemy : public GameObject
{
	private:
		// �G�l�~�[���f��
		std::unique_ptr<DirectX::Model> m_enemyModel;
		// �^�[�Q�b�g�|�C���^
		Player* m_target;
		//// �J�n�ʒu
		//MapPosition m_startPosition;
		//// �I���ʒu
		//MapPosition m_endPosition;
		//// �ŒZ�o�H
		//std::vector<MapPosition> m_route;
		//// �ړ��s��
		//DirectX::SimpleMath::Matrix m_translation;

		// ���݂̏��
		CharacterState* m_currentState;

	public:
		Enemy(Player* player);
		~Enemy();

		void Update()override;
		void Render()override;
		// �����蔻��
		virtual void OnCollision(GameObject* object)override;

		// ���݂̏�Ԃ��擾
		CharacterState* GetCurrentState() { return m_currentState; }

		// ��ԑJ��
		void ChangeState(CharacterState* state){ m_currentState = state; }

		//// �J�n�ʒu���擾����
		//MapPosition GetStartPosition()
		//{
		//	return m_startPosition;
		//}
		//// �J�n�ʒu��ݒ肷��
		//void SetStartPosition(const MapPosition& startPosition)
		//{
		//	m_startPosition = startPosition;
		//}
		//// �I���ʒu���擾����
		//MapPosition GetEndPosition()
		//{
		//	return m_endPosition;
		//}
		//// �I���ʒu��ݒ肷��
		//void SetEndPosition(const MapPosition& endPosition)
		//{
		//	m_endPosition = endPosition;
		//}

		//// �ŒZ�o�H���擾����
		//std::vector<MapPosition> GetRoute()
		//{
		//	return m_route;
		//}

};

