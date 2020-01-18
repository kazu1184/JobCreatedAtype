#include "pch.h"
#include "Enemy.h"

#include <Effects.h>
#include "DeviceResources.h"

#include "Transform.h"
#include "MapPosition.h"
#include "ModelMap.h"
#include "Player.h"
#include "GameContext.h"
#include "FollowCamera.h"
#include "GameObjectManager.h"
#include "CollisionManager.h"

#include "CharacterState.h"
#include "Idling.h"
#include "Chasing.h"
#include "Searching.h"

Enemy::Enemy(Player * player)
	: GameObject("Enemy")
	, m_row(0)
	, m_colum(0)
{
	// ���f���f�[�^�̓ǂݍ���
	DirectX::EffectFactory fx(GameContext<DX::DeviceResources>::Get()->GetD3DDevice());
	fx.SetDirectory(L"Resources\\Models");
	m_enemyModel = DirectX::Model::CreateFromCMO(GameContext<DX::DeviceResources>::Get()->GetD3DDevice(), L"Resources\\Models\\Enemy.cmo", fx);

	// Idling�I�u�W�F�N�g�𐶐�����
	m_idlingState = std::make_unique<Idling>();
	// Idling�I�u�W�F�N�g������������
	m_idlingState->Initialize(this);

	// Searching�I�u�W�F�N�g�𐶐�����
	m_searchingState = std::make_unique<Searching>();
	// Searching�I�u�W�F�N�g������������
	m_searchingState->Initialize(this);

	// Chasing�I�u�W�F�N�g�𐶐�����
	m_chasingState = std::make_unique<Chasing>();
	// Chasing�I�u�W�F�N�g������������
	m_chasingState->Initialize(this);

	// ���݂̏�Ԃ��A�C�h�����O��Ԃɐݒ肷��
	ChangeState(m_idlingState.get());
	
	// �R���|�[�l���g��ǉ�
	m_transform = AddComponent<Transform>();
	m_startPosition = AddComponent<MapPosition>();
	m_endPosition = AddComponent<MapPosition>();
	// �|�W�V������␳����
	m_transform->SetPosition(DirectX::SimpleMath::Vector3(m_startPosition->GetX() * ModelMap::MAP_SIZE + ModelMap::MAP_SIZE / 2, 0.0f, m_startPosition->GetY() * ModelMap::MAP_SIZE + ModelMap::MAP_SIZE / 2));
	m_transform->SetScale(DirectX::SimpleMath::Vector3(0.1f, 0.1f, 0.1f));
	// �v���C���[�|�C���^�̑��
	m_target = player;

}

Enemy::~Enemy()
{
}

void Enemy::Update()
{
	// �R���|�[�l���g�̍X�V
	GameObject::Update();

	// ���݂̏�Ԃ��X�V����
	bool result = m_currentState->Update();

	if (m_currentState == m_idlingState.get())
	{
		// �J�n�ʒu�̍X�V
		SetStartPosition(new MapPosition(m_row,m_colum));
		// �J�n�ʒu���擾����
		MapPosition* startPosition = GetStartPosition();
		// �G�̈ʒu��ݒ肷��
		m_transform->SetPosition(DirectX::SimpleMath::Vector3(startPosition->GetX() * ModelMap::MAP_SIZE + ModelMap::MAP_SIZE / 2, 0.0f, startPosition->GetY() * ModelMap::MAP_SIZE + ModelMap::MAP_SIZE / 2));
		// �I���ʒu��ݒ肷��
		MapPosition* endPosition = m_target->GetMapPosition();
		SetEndPosition(endPosition);
		m_row = endPosition->GetX();
		m_colum = endPosition->GetY();
		// ���݂̏�Ԃ��T�[�`��Ԃɐݒ肷��
		ChangeState(GetSearchingState());
	}
	// �T�[�`���(�ŒZ�o�H�̒T����)�̍X�V��
	else if (m_currentState == m_searchingState.get())
	{
		// �T�[�`��Ԃ��X�V����A����I���̏ꍇ
		if (result)
		{
			// �ŒZ�o�H���擾����
			m_route = m_searchingState.get()->GetRoute();
			// ���݂̏�Ԃ�ǐՏ�ԂɕύX����
			ChangeState(m_chasingState.get());
		}
		else
		{
			// ���݂̏�Ԃ��A�C�h�����O��ԂɕύX����
			ChangeState(m_idlingState.get());
		}
	}
	// �ǐՏ�Ԃ̍X�V��
	else if (m_currentState == m_chasingState.get())
	{
		// �ǐՏ�Ԃ��X�V����A����I���̏ꍇ
		if (result)
		{
			// �ǐՒ�(��Ԃ�ύX���Ȃ�)
		}
		else
		{
			// �ǐՂ��I�������̂Ō��݂̏�Ԃ��A�C�h�����O��ԂɕύX����
			ChangeState(m_idlingState.get());
		}
	}
}

void Enemy::Render()
{
	DX::DeviceResources* deviceResources = GameContext<DX::DeviceResources>::Get();
	FollowCamera* camera = GameContext<GameObjectManager>::Get()->GetCamera();
	// �G�l�~�[���f���̕`��
	m_enemyModel->Draw(deviceResources->GetD3DDeviceContext(),
		*GameContext<DirectX::CommonStates>::Get(),
		m_transform->GetWorld(), camera->GetView(), camera->GetProjection());

}

void Enemy::OnCollision(GameObject * object)
{
}
