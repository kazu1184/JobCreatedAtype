#pragma once
#include "GameObject.h"

#include <Model.h>

class CharacterState;
class Idling;
class Chasing;
class Searching;
class MapPosition;
class Player;

class Enemy : public GameObject
{
	private:
		// �G�l�~�[���f��
		std::unique_ptr<DirectX::Model> m_enemyModel;
		// �^�[�Q�b�g�|�C���^
		Player* m_target;
		// �J�n�ʒu
		MapPosition* m_startPosition;
		// �I���ʒu
		MapPosition* m_endPosition;
		// �ŒZ�o�H
		std::vector<MapPosition*> m_route;
		// �ړ��s��
		DirectX::SimpleMath::Matrix m_translation;

		// ���݂̏��
		CharacterState* m_currentState;
		// �A�C�h�����
		std::unique_ptr<Idling> m_idlingState;
		// �T�����
		std::unique_ptr<Searching> m_searchingState;
		// �ǐՏ��
		std::unique_ptr<Chasing> m_chasingState;

	public:
		Enemy(Player* player);
		~Enemy();

		void Update()override;
		void Render()override;
		// �����蔻��
		virtual void OnCollision(GameObject* object)override;

		// ���݂̏�Ԃ��擾
		CharacterState* GetCurrentState() { return m_currentState; }

		// Idling��Ԃ��擾����
		Idling* GetIdlingState() const
		{
			return m_idlingState.get();
		}

		// Searching��Ԃ��擾����
		Searching* GetSearchingState() const
		{
			return m_searchingState.get();
		}

		// Chasing��Ԃ��擾����
		Chasing* GetChasingState() const
		{
			return m_chasingState.get();
		}

		// ��ԑJ��
		void ChangeState(CharacterState* state){ m_currentState = state; }

		// �J�n�ʒu���擾����
		MapPosition* GetStartPosition()
		{
			return m_startPosition;
		}
		// �J�n�ʒu��ݒ肷��
		void SetStartPosition(MapPosition* startPosition)
		{
			m_startPosition = startPosition;
		}
		// �I���ʒu���擾����
		MapPosition* GetEndPosition()
		{
			return m_endPosition;
		}
		// �I���ʒu��ݒ肷��
		void SetEndPosition(MapPosition* endPosition)
		{
			m_endPosition = endPosition;
		}

		// �ŒZ�o�H���擾����
		std::vector<MapPosition*> GetRoute()
		{
			return m_route;
		}

};

