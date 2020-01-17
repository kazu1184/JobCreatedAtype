#pragma once
#include "Node.h"
#include "TiledMap.h"
#include "vector"
#include "MapPosition.h"

class A_Star
{
	public:	// �萔�̒�`

		// �T���ߗ׍s��
		static const int NEIGHBOR_ROW_NUM = 4;
		// �T���ߗח�
		static const int NEIGHBOR_COLUMN_NUM = 2;
		// �s��
		enum ROW_COLUMN { ROW = 0, COLUMN = 1 };
		// �s��I�t�Z�b�g
		const int OFFSET[NEIGHBOR_ROW_NUM][NEIGHBOR_COLUMN_NUM] = 
		{ 
			{ -1,  0 },
			{  0, -1 },
			{  0,  1 },
			{  1,  0 }
		};

	private: // �����o�ϐ�

		// �}�b�v�s
		int m_mapRow;
		// �}�b�v��
		int m_mapColumn;
		// �I�[�v�����X�g
		std::vector<Node*> m_openList;
		// �N���[�Y�h���X�g
		std::vector<Node*> m_closedList;
	
		// TiledMap�I�u�W�F�N�g�ւ̃|�C���^
		TiledMap* m_tiledMap;
		// Node�I�u�W�F�N�g�ւ̃|�C���^���i�[����}�b�v�z��
		std::vector<std::vector<Node*>> m_astarMap;

	public: // �����o�֐�

		// �R���X�g���N�^
		A_Star(TiledMap* tiledMap);
		// �f�X�g���N�^
		~A_Star();

		// 2�_�Ԃ̋������v�Z����
		float Distance(MapPosition* position, MapPosition* position1);
		// �ŒZ�o�H�I�u�W�F�N�g������������
		bool Initialize();
		// Node�I�u�W�F�N�g�}�b�v���N���A����
		void ClearMap();
		// �ŒZ�o�H�A���S���Y�������s����
		bool Search(MapPosition* startPosition, MapPosition* endPosition);
		// �ŒZ�o�H��Ԃ�
		std::vector<MapPosition*> GetShortestPath(MapPosition* startPosition, MapPosition* endPosition);
		// ��n��������
		void Finalize();
};

