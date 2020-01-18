#include "pch.h"
#include "Chasing.h"
#include "Enemy.h"
#include "MapPosition.h"
#include "ModelMap.h"
#include "Transform.h"

// �R���X�g���N�^
Chasing::Chasing() : m_index(0), m_sum_translation(0.0f), m_position(DirectX::SimpleMath::Vector3::Zero)
{

}

bool Chasing::Initialize(GameObject * object)
{
	// Enemy�I�u�W�F�N�g�ŃL���X�g����
	m_enemy = static_cast<Enemy*>(object);
	return true;
}

bool Chasing::Update(DirectX::Keyboard::KeyboardStateTracker * keyboard)
{
	// �O�������̑��x
	DirectX::SimpleMath::Vector3 Forward(0.1f, 0.0f, 0.0f);

	// �ŒZ�o�H�z��0�̏ꍇ
	if (m_route.size() == 0)
	{
		// �J�n�ʒu���擾����
		MapPosition* position = m_enemy->GetStartPosition();
		// �ʒu��␳����
		m_position = DirectX::SimpleMath::Vector3((float)position->GetX()* ModelMap::MAP_SIZE + ModelMap::MAP_SIZE / 2, 0.0f, (float)position->GetY()* ModelMap::MAP_SIZE + ModelMap::MAP_SIZE / 2);
		// �ŒZ�o�H���擾����
		m_route = m_enemy->GetRoute();
	}

	// ���݂̈ʒu�Ǝ��̈ʒu�̍����v�Z����
	DirectX::SimpleMath::Vector2 direction((float)m_route[m_index + 1]->GetX() - m_route[m_index]->GetX(),
		(float)m_route[m_index + 1]->GetY() - m_route[m_index]->GetY());
	// �������v�Z����
	float angle = -atan2(direction.y, direction.x);
	// ��]�p���v�Z����
	DirectX::SimpleMath::Matrix rotation = DirectX::SimpleMath::Matrix::CreateRotationY(angle);
	// ���x���v�Z����
	DirectX::SimpleMath::Vector3 velocity = DirectX::SimpleMath::Vector3::TransformNormal(Forward, rotation);
	// �ړ��x�N�g����ώZ����
	m_sum_translation += velocity.Length();
	// �ړ��x�N�g�����ʒu�ɉ��Z����
	m_position += velocity;
	// �G�̈ʒu��ݒ肷��
	m_enemy->GetTransform()->SetPosition(DirectX::SimpleMath::Vector3(m_position.x , 0.0f, m_position.z));
	// �ړ��x�N�g���̐ώZ
	if (m_sum_translation >= ModelMap::MAP_SIZE)
	{
		// �ړ��x�N�g���̐ώZ�����Z�b�g����
		m_sum_translation = 0.0f;
		// �C���f�b�N�X���z�񐔂𒴂��Ȃ��ꍇ
		if (m_index < (int)m_route.size() - 2)
		{
			// �C���f�b�N�X�����Z����
			m_index++;
		}
		else
		{
			// �����l�ɖ߂�
			m_index = 0;
			// �I���ʒu�܂œ��B������ŒZ�o�H�z����N���A����
			m_route.clear();
			return false;
		}
	}
	return true;
}

// ��n��������
bool Chasing::Finalize()
{
	return true;
}
