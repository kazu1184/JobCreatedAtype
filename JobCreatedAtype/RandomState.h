#pragma once
#include "CharacterState.h"

class Enemy;
class ModelMap;
class MapPosition;

class RandomState : public CharacterState
{
	public:
		// �v�l����
		static const int THINKING_INTERVAL;

	private: 
		// �G�l�~�[
		Enemy* m_enemy;
		// ���x
		DirectX::SimpleMath::Vector3 m_velocity;
		// �G�l�~�[�̃}�b�v�|�W�V����
		MapPosition* m_currentMapPos;
		// ����
		int m_direction;
		// ����
		int m_count;
		// �}�b�v�|�C���^
		ModelMap* m_map;
	
	public:
		// �R���X�g���N�^
		RandomState();

		// ����������
		bool Initialize(GameObject* object)override;
		// �X�V����
		bool Update(DirectX::Keyboard::KeyboardStateTracker* keyboard = nullptr)override;
		// ��n��������
		bool Finalize()override;

	private:
		// �t���[�g���ׂ�
		inline bool FloatEquals(float a, float b)
		{
			if (std::abs(a - b) <= std::numeric_limits<float>::epsilon())
			{
				return true;
			}
			else
			{
				return false;
			}
		}
};

