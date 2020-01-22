//======================================================
// File Name	: TitleState.cpp
// Summary		: タイトルステイト
// Date			: 2019/011/19
// Author		: Kazuaki Hashimoto
//======================================================

#include "pch.h"
#include "TitleState.h"

#include "DebugFont.h"
#include "GameContext.h"
#include "GameStateManager.h"
#include "DeviceResources.h"
 
#include <WICTextureLoader.h>
#include <Keyboard.h>

TitleState::TitleState()
	: GameState()
{
}

TitleState::~TitleState()
{
}

void TitleState::Initialize()
{
	Microsoft::WRL::ComPtr<ID3D11Resource> resource;
	DirectX::CreateWICTextureFromFile(GameContext<DX::DeviceResources>::Get()->GetD3DDevice(),
		L"Resources\\Textures\\title.png", resource.GetAddressOf(), m_resultTexture.GetAddressOf());
}

void TitleState::Update()
{

	DirectX::Keyboard::State keyState = DirectX::Keyboard::Get().GetState();
	if (keyState.IsKeyDown(DirectX::Keyboard::Space))
	{
		GameStateManager* gameStateManager = GameContext<GameStateManager>().Get();
		gameStateManager->PushState("Play");
	}
}

void TitleState::Render()
{
	DirectX::SpriteBatch* sprite = GameContext<DirectX::SpriteBatch>::Get();
	sprite->Begin();
	sprite->Draw(m_resultTexture.Get(), GameContext<DX::DeviceResources>::Get()->GetOutputSize());
	sprite->End();
}
 
void TitleState::Finalize()
{
}
