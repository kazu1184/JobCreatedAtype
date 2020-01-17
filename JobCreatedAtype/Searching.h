#pragma once
#include "TiledMap.h"
#include "A_Star.h"
#include "StepTimer.h"
#include "CharacterState.h"

class Enemy;
class MapPosition;

class Searching : public CharacterState
{
	private: // �����o�֐�

		// Enemy�I�u�W�F�N�g�ւ̃|�C���^
		Enemy* m_enemy;
	
		// �}�b�v�t�@�C��
		std::string m_mapFile;
		// �^�C���h�}�b�v
		std::unique_ptr<TiledMap> m_tiledMap;
		// �ŒZ�o�H�T��
		std::unique_ptr<A_Star> m_pathFinding;
		// �ŒZ�o�H
		std::vector<MapPosition*> m_route;
		// �J�n�ʒu
		MapPosition* m_startPosition;
		// �I���ʒu
		MapPosition* m_endPosition;

	public: // �����o�֐�
		
			// �R���X�g���N�^
			Searching();
			// ����������
			bool Initialize(GameObject* object)override;
			// �X�V����
			bool Update(DirectX::Keyboard::KeyboardStateTracker* keyboard = nullptr)override;
			// ��n��������
			bool Finalize()override;

			// �J�n�ʒu���擾����
			MapPosition* GetStartPosition()
			{
				return m_startPosition;
			}
			// �I���ʒu���擾����
			MapPosition* GetEndPosition()
			{
				return m_endPosition;
			}

			// �ŒZ�o�H���擾����
			std::vector<MapPosition*> GetRoute() const
			{
				return m_route;
			}
};