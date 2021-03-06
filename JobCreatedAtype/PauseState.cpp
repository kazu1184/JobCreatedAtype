#include "pch.h"

#include <Keyboard.h>

#include "PauseState.h"
#include "DebugFont.h"
#include "GameContext.h"
#include "GameStateManager.h"

PauseState::PauseState()
	:GameState()
{
}


PauseState::~PauseState()
{
}

void PauseState::Initialize()
{
}

void PauseState::Update()
{
	DirectX::Keyboard::State keyState = DirectX::Keyboard::Get().GetState();
	if (keyState.IsKeyDown(DirectX::Keyboard::Z))
	{
		GameStateManager* gameStateManager = GameContext<GameStateManager>().Get();
		gameStateManager->RequestState("Title");
	}

	if (keyState.IsKeyDown(DirectX::Keyboard::X))
	{
		GameStateManager* gameStateManager = GameContext<GameStateManager>().Get();
		gameStateManager->PopState();
	}
}

void PauseState::Render()
{
	DebugFont* debugFont = DebugFont::GetInstance();
	debugFont->print(300, 280, L"[Z] Title   [X] Play");
	debugFont->draw();
}

void PauseState::Finalize()
{
}
