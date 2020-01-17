//======================================================
// File Name	: StandState.h
// Summary		: 静止状態
// Date			: 2019/12/29
// Author		: Kazuaki Hashimoto
//======================================================
#include "pch.h"
#include "StandState.h"
#include "MoveState.h"

#include "GameObject.h"
#include "GameObjectManager.h"
#include "GameContext.h"
#include "Player.h"
#include "Transform.h"
#include "FollowCamera.h"

StandState::StandState()
{
}


StandState::~StandState()
{

}

bool StandState::Initialize(GameObject * obj)
{
	// スタティックキャスト
	m_player = static_cast<Player*>(obj);
	return true;
}

bool StandState::Update(DirectX::Keyboard::KeyboardStateTracker * keyboard)
{
	if (keyboard->IsKeyPressed(DirectX::Keyboard::Keys::Up))
	{
		m_player->SetDirection(Player::DIRECTION::FORWARD);
		m_player->ChangeState(m_player->GetMove());
	}

	if (keyboard->IsKeyPressed(DirectX::Keyboard::Keys::Down))
	{
		m_player->SetDirection(Player::DIRECTION::BACKWARD);
		m_player->ChangeState(m_player->GetMove());
	}

	return true;
}

bool StandState::Finalize()
{
	return true;
}
