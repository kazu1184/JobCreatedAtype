#include "pch.h"
#include "Searching.h"
#include "Enemy.h"
#include "ModelMap.h"
#include "MapPosition.h"

// �R���X�g���N�^
Searching::Searching(const std::string& mapFile)
	: 
	m_mapFile(mapFile) 										// �}�b�v�t�@�C��
{
}

bool Searching::Initialize(GameObject* object)
{
	m_enemy = static_cast<Enemy*>(object);
	m_startPosition = new MapPosition(0, 0);
	m_endPosition = new MapPosition(0, 0);


	// TiledMap�I�u�W�F�N�g�𐶐�����
	m_tiledMap = std::make_unique<TiledMap>();
	// TiledMap�I�u�W�F�N�g������������
	m_tiledMap->Load(m_mapFile);
	// AStar�I�u�W�F�N�g�𐶐�����
	m_pathFinding = std::make_unique<A_Star>(m_tiledMap.get());
	// AStar�I�u�W�F�N�g������������
	m_pathFinding->Initialize();

	return true;
}

// �X�V����
bool Searching::Update(DirectX::Keyboard::KeyboardStateTracker* keyboard)
{
	// �J�n�ʒu���擾����
	m_startPosition = m_enemy->GetStartPosition();
	// �I���ʒu���擾����
	m_endPosition = m_enemy->GetEndPosition();
	// �ŒZ�o�H��T������
	if (m_pathFinding->Search(m_startPosition, m_endPosition) == false)
		return false;
	// �ŒZ�o�H���擾����
	m_route = m_pathFinding->GetShortestPath(m_startPosition, m_endPosition);
	// �}�b�v���N���A����
	m_pathFinding->ClearMap();
	// �G���[���`�F�b�N����
	if (m_route.size() == 0)
		return false;
	else
		return true;
}

// ��n��������
bool Searching::Finalize() 
{
	// �}�b�v���N���A����
	m_pathFinding->ClearMap();
	// AStar�I�u�W�F�N�g���������
	m_pathFinding.reset();
	// Map�I�u�W�F�N�g���������
	m_tiledMap.reset();

	return true;
}
