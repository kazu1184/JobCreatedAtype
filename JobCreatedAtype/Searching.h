#pragma once
#include "CharacterState.h"
#include "TiledMap.h"
#include "A_Star.h"
#include "StepTimer.h"

class MapPosition;
class Enemy;

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
			Searching(const std::string& mapFile);
			// ����������
			void Initialize(GameObject* object)override;
			// �X�V����
			void Update(DirectX::Keyboard::KeyboardStateTracker* keyboard)override;
			// ��n��������
			void Finalize()override;

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

//
//class Searching : public IState
//{
//public:
//	// �J�n�ʒu���擾����
//	Position GetStartPosition()
//	{
//		return m_startPosition;
//	}
//	// �I���ʒu���擾����
//	Position GetEndPosition()
//	{
//		return m_endPosition;
//	}
//
//	// �ŒZ�o�H���擾����
//	std::vector<Position> GetRoute() const
//	{
//		return m_route;
//	}
//
//	// �R���X�g���N�^
//	Searching(const std::string& mapFile);
//	// ����������
//	int Initialize(Enemy* object)override;
//	// �X�V����
//	int Update(const DX::StepTimer& timer)override;
//	// �`�悷��
//	void Render()override;
//	// ��n��������
//	void Finalize()override;
//private:
//	// Enemy�I�u�W�F�N�g�ւ̃|�C���^
//	Enemy* m_enemy;
//
//	// �}�b�v�t�@�C��
//	std::string m_mapFile;
//	// �^�C���h�}�b�v
//	std::unique_ptr<TiledMap> m_tiledMap;
//	// �ŒZ�o�H�T��
//	std::unique_ptr<A_Star> m_pathFinding;
//	// �ŒZ�o�H
//	std::vector<Position> m_route;
//	// �J�n�ʒu
//	Position m_startPosition;
//	// �I���ʒu
//	Position m_endPosition;
//};
//
//
