#include "pch.h"
#include "Enemy.h"

#include "Transform.h"
#include "MapPosition.h"
#include "ModelMap.h"
#include "Player.h"

#include "CharacterState.h"
#include "Idling.h"
#include "Chasing.h"
#include "Searching.h"

Enemy::Enemy(Player * player)
	: GameObject("Enemy")
	, m_startPosition(0)
	, m_endPosition(0)
{
	// Idling�I�u�W�F�N�g�𐶐�����
	m_idlingState = std::make_unique<Idling>();
	// Idling�I�u�W�F�N�g������������
	m_idlingState->Initialize(this);

	// Searching�I�u�W�F�N�g�𐶐�����
	m_searchingState = std::make_unique<Searching>(std::string("map.csv"));
	// Searching�I�u�W�F�N�g������������
	m_searchingState->Initialize(this);

	// Chasing�I�u�W�F�N�g�𐶐�����
	m_chasingState = std::make_unique<Chasing>();
	// Chasing�I�u�W�F�N�g������������
	m_chasingState->Initialize(this);

	// ���݂̏�Ԃ��A�C�h�����O��Ԃɐݒ肷��
	ChangeState(m_idlingState.get());

	// �|�W�V������␳����
	m_transform->SetPosition(DirectX::SimpleMath::Vector3(m_startPosition->GetX() * ModelMap::MAP_SIZE + ModelMap::MAP_SIZE / 2, 0.0f, m_startPosition->GetY() * ModelMap::MAP_SIZE + ModelMap::MAP_SIZE / 2));
	// �v���C���[�|�C���^�̑��
	m_target = player;

}

Enemy::~Enemy()
{
}

void Enemy::Update()
{
	GameObject::Update();

	// ���݂̏�Ԃ��X�V����
	bool result = m_currentState->Update();

	if (m_currentState == m_idlingState.get())
	{
		// �J�n�ʒu�̍X�V
		SetStartPosition(GetEndPosition());
		// �J�n�ʒu���擾����
		MapPosition* startPosition = GetStartPosition();
		// �G�̈ʒu��ݒ肷��
		m_transform->SetPosition(DirectX::SimpleMath::Vector3(startPosition->GetX() * ModelMap::MAP_SIZE + ModelMap::MAP_SIZE / 2, 0.0f, startPosition->GetY() * ModelMap::MAP_SIZE + ModelMap::MAP_SIZE / 2));
		// �I���ʒu��ݒ肷��
		SetEndPosition(m_target->GetMapPosition());
		// ���݂̏�Ԃ��T�[�`��Ԃɐݒ肷��
		ChangeState(GetSearchingState());
	}

	// �T�[�`���(�ŒZ�o�H�̒T����)�̍X�V��
	if (m_currentState == m_searchingState.get())
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
}

void Enemy::OnCollision(GameObject * object)
{
}
