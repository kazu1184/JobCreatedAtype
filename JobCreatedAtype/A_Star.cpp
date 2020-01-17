#include "pch.h"
#include "A_Star.h"

// �R���X�g���N�^
A_Star::A_Star(TiledMap* tiledMap) : m_tiledMap(tiledMap)
{
	// �}�b�v�s��ݒ肷��
	m_mapRow = m_tiledMap->GetMapRow();
	// �}�b�v���ݒ肷��
	m_mapColumn = m_tiledMap->GetMapColumn();
}

// �f�X�g���N�^
A_Star::~A_Star()
{
	// ��n��
	Finalize();
}


// 2�_�Ԃ̋������v�Z����
float A_Star::Distance(MapPosition* position, MapPosition* position1)
{
	// �s�����v�Z����
	int deltaRow = position1->GetX() - position->GetX();
	// �񍷂��v�Z����
	int deltaColumn = position1->GetY() - position->GetY();
	// �v�Z���ʂ�Ԃ�
	return (float)sqrt((deltaRow * deltaRow) + (deltaColumn * deltaColumn));
}
// �ŒZ�o�H�I�u�W�F�N�g������������
bool A_Star::Initialize()
{
	// astarMap�s�z����m�ۂ���
	m_astarMap.resize(m_mapRow);
	for (int row = 0; row < m_mapRow; row++)
	{
		// ��z����m�ۂ���
		m_astarMap[row].resize(m_mapColumn);
	}

	// Node�I�u�W�F�N�g�𐶐����}�b�v�Ɋi�[����
	for (int row = 0; row < m_mapRow; row++)
	{
		for (int column = 0; column < m_mapColumn; column++)
		{
			if (m_astarMap[row][column] == nullptr)
			{
				// Node�I�u�W�F�N�g�𐶐�����
				m_astarMap[row][column] = new Node(row, column, m_tiledMap->GetMap()[row][column]);
				if (m_astarMap[row][column] == nullptr)
					return false;
			}
		}
	}
	return true;
}

// Node�I�u�W�F�N�g�}�b�v���N���A����
void A_Star::ClearMap()
{
	// �I�[�v�����X�g���N���A����
	m_openList.clear();
	// �N���[�Y�h���X�g���N���A����
	m_closedList.clear();

	for (int row = 0; row < m_mapRow; row++)
	{
		for (int column = 0; column < m_mapColumn; column++)
		{
			// �R�X�g���N���A����
			m_astarMap[row][column]->SetCost(0.0f);
			// �q���[���X�e�B�b�N���N���A����
			m_astarMap[row][column]->SetHeuristic(0.0f);
			// �X�R�A���N���A����
			m_astarMap[row][column]->SetScore(0.0f);
		}
	}
}

// �ŒZ�o�H�A���S���Y�������s����
bool A_Star::Search(MapPosition* startPosition, MapPosition* endPosition)
{
	// �e�s��ݒ肷��
	int parentRow = endPosition->GetX();
	// �e���ݒ肷��
	int parentColumn = endPosition->GetY();

	for (;;)
	{	// �I�[�v�����X�g�ɋߗ׃m�[�h��ǉ�����
		for (int index = 0; index < NEIGHBOR_ROW_NUM; index++)
		{
			// �ߗ׃m�[�h�̍s�ʒu�����肷��
			int neighborRow = parentRow + OFFSET[index][ROW];
			// �ߗ׃m�[�h�̗�ʒu�����肷��
			int neighborColumn = parentColumn + OFFSET[index][COLUMN];

			// �}�b�v�̍s�ʒu�͈̔͂��`�F�b�N����
			if (neighborRow < 0 || neighborRow > m_mapRow - 1)
				continue;
			// �}�b�v�̗�ʒu�͈̔͂��`�F�b�N����
			if (neighborColumn < 0 || neighborColumn > m_mapColumn - 1)
				continue;
			// �ߗ׃m�[�h�̃X�R�A���v�Z�ς݂̏ꍇ�̓I�[�v�����X�g�ɒǉ����Ȃ�
			if (m_astarMap[neighborRow][neighborColumn]->GetScore() != 0.0f)
				continue;
			// �I���m�[�h���I�[�v�����X�g�ɒǉ����Ȃ�
			if (neighborRow == endPosition->GetX() && neighborColumn == endPosition->GetY())
				continue;
			// �m�[�h���p�X�̏ꍇ�I�[�v�����X�g�Ƀm�[�h��ǉ�����
			if (m_astarMap[neighborRow][neighborColumn]->GetAttribute() == TiledMap::MAP_ATTRIBUTE::P)
			{
				// �I�[�v�����X�g�Ƀm�[�h��ǉ�����
				m_openList.push_back(m_astarMap[neighborRow][neighborColumn]);
				// �m�[�h�̐e�m�[�h��ݒ肷��
				m_astarMap[neighborRow][neighborColumn]->SetParent(m_astarMap[parentRow][parentColumn]);
			}
		}
		// �I�[�v�����X�g����ɂȂ�ꍇ�A�o�H�����݂��Ȃ�
		if (m_openList.size() == 0)
			return false;

		// �I�[�v�����X�g�C�e���[�^��錾����
		std::vector<Node*>::iterator openListItr;
		// �I�[�v�����X�g�ɒǉ����ꂽ�m�[�h�̃X�R�A���v�Z����
		for (openListItr = m_openList.begin(); openListItr < m_openList.end(); openListItr++)
		{
			// �X�R�A�v�Z�ς݃m�[�h�͍Čv�Z���Ȃ�
			if ((*openListItr)->GetScore() != 0.0f)
				continue;
			// �m�[�h�̃R�X�g���v�Z����
			(*openListItr)->SetCost(Distance(new MapPosition(endPosition->GetX(), endPosition->GetY()), new MapPosition((*openListItr)->GetRow(), (*openListItr)->GetColumn())));
			// �m�[�h�̃q���[���X�e�B�b�N���v�Z����
			(*openListItr)->SetHeuristic(Distance(new MapPosition(startPosition->GetX(), startPosition->GetY()), new MapPosition((*openListItr)->GetRow(), (*openListItr)->GetColumn())));
			// �m�[�h�̃X�R�A���v�Z����
			(*openListItr)->SetScore((*openListItr)->GetCost() + (*openListItr)->GetHeuristic());
		}

		// �N���[�Y�h���X�g�C�e���[�^��錾����
		std::vector<Node*>::iterator closedListItr = m_openList.begin();
		// �ŏ��X�R�A
		float minimum = 0.0f;
		// �ŏ��X�R�A�̃m�[�h��T������
		for (openListItr = m_openList.begin(), minimum = (*openListItr)->GetScore(); openListItr < m_openList.end(); openListItr++)
		{
			// �ŏ��l�ƃI�[�v�����X�g�C�e���[�^���w�����m�[�h�̃X�R�A�Ɣ�r����
			if (minimum >(*openListItr)->GetScore())
			{
				// �ŏ��X�R�A��ݒ肷��
				minimum = (*openListItr)->GetScore();
				// �I�[�v�����X�g�C�e���[�^���N���[�Y�h���X�g�C�e���[�^�ɑ������
				closedListItr = openListItr;
			}
		}

		// �V�����e�s��ݒ肷��
		parentRow = (*closedListItr)->GetRow();
		// �V�����e���ݒ肷��
		parentColumn = (*closedListItr)->GetColumn();
		// �V�����e�m�[�h(�ŏ��X�R�A�̃m�[�h)���N���[�Y�h���X�g�C�e���[�^�ɒǉ�����
		m_closedList.push_back(*closedListItr);
		// �N���[�Y�h���X�g�C�e���[�^���w�����m�[�h���I�[�v�����X�g����폜����
		m_openList.erase(closedListItr);
		// �V�����e�m�[�h���X�^�[�g�m�[�h�ɓ��B�������ǂ����𔻒肷��
		if (parentRow == startPosition->GetX() && parentColumn == startPosition->GetY())
			break;
	}
	return true;
}

// �ŒZ�o�H��Position�z���Ԃ�
std::vector<MapPosition*> A_Star::GetShortestPath(MapPosition* startPosition, MapPosition* endPosition)
{
	std::vector<MapPosition*> shortestPath;
	// �m�[�h�ɊJ�n�m�[�h��ݒ肷��
	Node* node = m_astarMap[startPosition->GetX()][startPosition->GetY()];
	// �m�[�h���I���m�[�h�ɓ��B�������ǂ����𔻒肷��
	while (node != m_astarMap[endPosition->GetX()][endPosition->GetY()])
	{
		// �ŒZ�o�H�̈ʒu��Position�z��ɒǉ�����
		shortestPath.push_back(new MapPosition(node->GetRow(), node->GetColumn()));
		// �e�m�[�h��H��
		node = node->GetParent();
	}
	// �ŒZ�o�H�̈ʒu��Position�z��ɒǉ�����
	shortestPath.push_back(new MapPosition(node->GetRow(), node->GetColumn()));
	// �ŒZ�o�H��Position�z���Ԃ�
	return shortestPath;
}

// ��n��������
void A_Star::Finalize()
{
	// �}�b�v�����̂��ׂĂ�Node�I�u�W�F�N�g��j������
	for (int row = 0; row < m_mapRow; row++)
	{
		for (int column = 0; column < m_mapColumn; column++)
		{
			// Node�I�u�W�F�N�g��j������
			if (m_astarMap[row][column] != nullptr)
			{
				delete m_astarMap[row][column];
				m_astarMap[row][column] = nullptr;
			}
		}
	}

	// �}�b�v�f�[�^��j������
	m_astarMap.clear();
}


