#include "pch.h"
#include "Idling.h"
#include "Enemy.h"

// コンストラクタ
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

// 後始末をする
void Idling::Finalize()
{
}
