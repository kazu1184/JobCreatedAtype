#include "pch.h"
#include "Idling.h"
#include "Enemy.h"

// �R���X�g���N�^
Idling::Idling()
{
}

// ����������
bool Idling::Initialize(GameObject* object)
{
	m_enemy = static_cast<Enemy*>(object);
	return true;
}

// �X�V����
bool Idling::Update(DirectX::Keyboard::KeyboardStateTracker* keyboard)
{
	return true;
}

// ��n��������
bool Idling::Finalize()
{
	return true;
}
