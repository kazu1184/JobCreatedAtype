//======================================================
// File Name	: ResultState.cpp
// Summary		: リザルトステイト
// Date			: 2019/01/19
// Author		: Kazuaki Hashimoto
//======================================================
#include "pch.h"
#include "ResultState.h"

#include "DebugFont.h"
#include "GameContext.h"
#include "GameStateManager.h"
#include "DeviceResources.h"

#include <WICTextureLoader.h>

ResultState::ResultState()
	: GameState()
	, m_count(0)
{
}


ResultState::~ResultState()
{
}

void ResultState::Initialize()
{
	m_count = 0;

	Microsoft::WRL::ComPtr<ID3D11Resource> resource;
	DirectX::CreateWICTextureFromFile(GameContext<DX::DeviceResources>::Get()->GetD3DDevice(),
		L"Resources\\Textures\\GameOver.png", resource.GetAddressOf(), m_resultTexture.GetAddressOf());
}

void ResultState::Update()
{
	m_count++;

	if (m_count > 120)
	{
		GameStateManager* gameStateManager = GameContext<GameStateManager>().Get();
		gameStateManager->RequestState("Title");
		m_count = 0;
	}
}

void ResultState::Render()
{
	DirectX::SpriteBatch* sprite = GameContext<DirectX::SpriteBatch>::Get();
	sprite->Begin();
	sprite->Draw(m_resultTexture.Get(), GameContext<DX::DeviceResources>::Get()->GetOutputSize());
	sprite->End();

	DebugFont* debugFont = DebugFont::GetInstance();
	debugFont->print(10, 10, L"ResultState");
	debugFont->draw();
	debugFont->print(10, 40, L"%3d / 120", m_count);
	debugFont->draw();
}

void ResultState::Finalize()
{
}
