#include "pch.h"
#include "Searching.h"
#include "Enemy.h"
#include "ModelMap.h"
#include "MapPosition.h"
#include "GameObjectManager.h"
#include "GameContext.h"

// �R���X�g���N�^
Searching::Searching()
{
}


bool Searching::Initialize(GameObject* object)
{
	m_enemy = static_cast<Enemy*>(object);
	m_startPosition = new MapPosition(0, 0);
	m_endPosition = new MapPosition(0, 0);
	// �}�b�v�̌���
	ModelMap* map = static_cast<ModelMap*>(GameContext<GameObjectManager>::Get()->Find("Map")[0]);
	// AStar�I�u�W�F�N�g�𐶐�����
	m_pathFinding = std::make_unique<A_Star>(map->GetTiledMap());
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
	// �J�n�ʒu�ƏI���|�C���^�̍폜
	delete m_startPosition;
	delete m_endPosition;

	return true;
}
