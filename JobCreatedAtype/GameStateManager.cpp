//======================================================
// File Name	: GameStateManager.h
// Summary		: ステイトマネージャー
// Date			: 2019/011/19
// Author		: Kazuaki Hashimoto
//======================================================
#include "pch.h"

#include <algorithm>

#include "GameStateManager.h"
#include "GameState.h"
#include "Utilities.h"

void GameStateManager::ChangeState()
{
	m_states.push_back(m_stateFactories[m_nextStateName]());
	m_states.back()->Initialize();

	m_nextStateName.clear();
}

GameStateManager::GameStateManager()
	: m_stateFactories()
	, m_states()
	, m_popCount(0)
	, m_nextStateName()
{
}


GameStateManager::~GameStateManager()
{
}

void GameStateManager::Update(float elapsedTime)
{
	elapsedTime;

	if (m_popCount > 0)
	{
		for (int i = 0; i < m_popCount; i++)
		{
			m_states.back()->Finalize();
			m_states.pop_back();
		}
		m_popCount = 0;
	}

	// 次のシーンがあればシーンを変える
	if (!m_nextStateName.empty())
	{
		ChangeState();
	}

	m_states.back()->Update();
}

void GameStateManager::Render()
{
	for (const std::unique_ptr<GameState>& state : m_states)
	{
		state->Render();
	}
}

void GameStateManager::RequestState(const std::string & stateName)
{
	m_popCount = m_states.size();
	m_nextStateName = stateName;
}

void GameStateManager::PushState(const std::string & stateName)
{
	m_nextStateName = stateName;
}

void GameStateManager::PopState(int count)
{
	if (!m_nextStateName.empty())
	{
		m_nextStateName.clear();
		count--;
	}

	m_popCount = Clamp<int>(m_popCount + count, 0, m_states.size() - 1);
}
