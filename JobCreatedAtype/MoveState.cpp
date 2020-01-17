//======================================================
// File Name	: MoveState.cpp
// Summary		: 動き状態
// Date			: 2019/12/29
// Author		: Kazuaki Hashimoto
//======================================================
#include "pch.h"
#include "MoveState.h"
#include "StandState.h"

#include "GameObject.h"
#include "GameObjectManager.h"
#include "GameContext.h"
#include "Player.h"
#include "Transform.h"
#include "FollowCamera.h"

const float MoveState::PLAYER_SPEED = 0.3f;

MoveState::MoveState()
{
}


MoveState::~MoveState()
{
}

bool MoveState::Initialize(GameObject * obj)
{
	// スタティックキャスト
	m_player = static_cast<Player*>(obj);
	return true;
}

bool MoveState::Update(DirectX::Keyboard::KeyboardStateTracker * keyboard)
{
	DirectX::SimpleMath::Vector3 dir = GameContext<GameObjectManager>::Get()->GetCamera()->getEye();
	dir.Normalize();
	dir.y = 0.0f;

	if (m_player->GetDirection() == Player::DIRECTION::FORWARD)
	{
		Transform* tr = m_player->GetTransform();
		tr->SetPosition(tr->GetPosition() + dir * -PLAYER_SPEED);
	}

	if (m_player->GetDirection() == Player::DIRECTION::BACKWARD)
	{
		Transform* tr = m_player->GetTransform();
		tr->SetPosition(tr->GetPosition() + dir * PLAYER_SPEED);
	}

	if (keyboard->IsKeyReleased(DirectX::Keyboard::Keys::Up)||
		keyboard->IsKeyReleased(DirectX::Keyboard::Keys::Down))
	{
		m_player->SetDirection(Player::DIRECTION::NONE);
		m_player->ChangeState(m_player->GetStand());
	}

	return true;
}

bool MoveState::Finalize()
{
	return true;
}
