#include "pch.h"
#include "KnockBackState.h"
#include "MoveState.h"
#include "StandState.h"

#include "GameContext.h"
#include "Transform.h"
#include "Player.h"
#include "FollowCamera.h"
#include "GameObjectManager.h"

const float KnockBackState::KNOCK_BACK_TIME = 15;

KnockBackState::KnockBackState()
	:m_time(0.0f)
{
}


KnockBackState::~KnockBackState()
{
}

void KnockBackState::Initialize(GameObject * obj)
{
	// スタティックキャスト
	m_player = static_cast<Player*>(obj);
}

void KnockBackState::Update(DirectX::Keyboard::KeyboardStateTracker * keyboard)
{
	//ToDo knockback
	DirectX::SimpleMath::Vector3 dir = GameContext<GameObjectManager>::Get()->GetCamera()->getEye();
	dir.Normalize();
	dir.y = 0.0f;

	if (m_player->GetDirection() == Player::DIRECTION::FORWARD)
	{
		Transform* tr = m_player->GetTransform();
		tr->SetPosition(tr->GetPosition() + dir * MoveState::PLAYER_SPEED);
	
		m_time++;
		if (m_time >= KNOCK_BACK_TIME)
		{
			m_time = 0.0f;
			m_player->ChangeState(m_player->GetStand());
		}
	}
	if (m_player->GetDirection() == Player::DIRECTION::BACKWARD)
	{
		Transform* tr = m_player->GetTransform();
		tr->SetPosition(tr->GetPosition() + dir * -MoveState::PLAYER_SPEED);

		m_time++;
		if (m_time >= KNOCK_BACK_TIME / 2)
		{
			m_time = 0.0f;
			m_player->ChangeState(m_player->GetStand());
		}
	}
}

void KnockBackState::Finalize()
{
}
