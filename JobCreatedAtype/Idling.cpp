#include "pch.h"
#include "Idling.h"
#include "Enemy.h"

// �R���X�g���N�^
Idling::Idling()
{
}

void Idling::Initialize(GameObject * object)
{
	m_enemy = static_cast<Enemy*>(object);
}

void Idling::Update(DirectX::Keyboard::KeyboardStateTracker * keyboard)
{
}

// ��n��������
void Idling::Finalize()
{
}
