#include "pch.h"
#include "Idling.h"
#include "Enemy.h"

// コンストラクタ
Idling::Idling()
{
}

// 初期化する
bool Idling::Initialize(GameObject* object)
{
	m_enemy = static_cast<Enemy*>(object);
	return true;
}

// 更新する
bool Idling::Update(DirectX::Keyboard::KeyboardStateTracker* keyboard)
{
	return true;
}

// 後始末をする
bool Idling::Finalize()
{
	return true;
}
