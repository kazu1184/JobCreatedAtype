//======================================================
// File Name	: PlayState.cpp
// Summary		: プレイステイト
// Date			: 2019/011/19
// Author		: Kazuaki Hashimoto
//======================================================

#include "pch.h"

#include <Keyboard.h>

#include "ADX2LE\Adx2Le.h"
#include "Resources\Audio\bgm_acf.h"

#include "PlayState.h"
#include "DebugFont.h"
#include "GameContext.h"
#include "Player.h"
#include "Enemy.h"
#include "Coin.h"
#include "FollowCamera.h"
#include "ModelMap.h"

#include "GameStateManager.h"
#include "GameObjectManager.h"
#include "CollisionManager.h"
#include "DeviceResources.h"
#include "Effects.h" 
#include "CommonStates.h"

PlayState::PlayState()
	: GameState()
{
}


PlayState::~PlayState()
{
}

void PlayState::Initialize()
{
	// コリジョンマネジャー
	m_collisionManager = std::make_unique<CollisionManager>();
	m_collisionManager->AllowCollision("Player", "Floor");
	m_collisionManager->AllowCollision("Building", "Player");
	m_collisionManager->AllowCollision("Floor", "Enemy");
	m_collisionManager->AllowCollision("Player", "Enemy");
	m_collisionManager->AllowCollision("Building", "Camera");
	m_collisionManager->AllowCollision("Coin", "Player");
	m_collisionManager->AllowCollision("Goal", "Player");
	GameContext<CollisionManager>::Register(m_collisionManager);

	// オブジェクトマネージャー生成・登録
	m_objectManager = std::make_unique<GameObjectManager>();
	GameContext<GameObjectManager>::Register(m_objectManager);

	// マップの生成・登録
	std::unique_ptr<ModelMap> map = std::make_unique<ModelMap>();
	m_objectManager->Add(std::move(map));

	// プレイヤー・エネミーの登録
	std::unique_ptr<Player> player = std::make_unique<Player>();
	std::unique_ptr<Enemy> enemy = std::make_unique<Enemy>(player.get());
	m_objectManager->Add(std::move(player));
	m_objectManager->Add(std::move(enemy));

	// コインオブジェクトの生成・登録
	std::unique_ptr<Coin> coin = std::make_unique<Coin>();
	m_objectManager->Add(std::move(coin));

	// オーディオの登録
	m_audio = std::make_unique<Adx2Le>();
	GameContext<Adx2Le>::Register(m_audio);

	m_audio->Initialize(L"Resources\\Audio\\bgm.acf");
	m_audio->LoadAcbFile(L"Resources\\Audio\\Bgm.acb");
	m_audio->Play(CRI_BGM_ACF_AISACCONTROL_AISACCONTROL_00);


	DirectX::EffectFactory* factory = new DirectX::EffectFactory(GameContext<DX::DeviceResources>::Get()->GetD3DDevice());
	// テクスチャの読み込みパス指定 
	factory->SetDirectory(L"Resources/Models");
	// 天球
	m_pSkyDoom = DirectX::Model::CreateFromCMO(
		GameContext<DX::DeviceResources>::Get()->GetD3DDevice(),
		L"Resources/Models/skydoom.cmo",
		*factory
	);
	delete factory;
}

void PlayState::Update()
{
	DirectX::Keyboard::State keyState = DirectX::Keyboard::Get().GetState();
	if (keyState.IsKeyDown(DirectX::Keyboard::P))
	{
		GameStateManager* gameStateManager = GameContext<GameStateManager>().Get();
		gameStateManager->PushState("Pause");
	}

	GameContext<GameObjectManager>::Get()->Update();

	GameContext<CollisionManager>::Get()->DetectCollision();

	m_audio->Update();

	if (!m_audio->IsPlayEndedByID(0)&&!m_audio->IsPlayingByID(1))
	{
		m_audio->Play(CRI_BGM_ACF_AISACCONTROL_AISACCONTROL_00);
	}
}

void PlayState::Render()
{
	m_pSkyDoom->Draw(GameContext<DX::DeviceResources>::Get()->GetD3DDeviceContext()
		, *GameContext<DirectX::CommonStates>::Get(), DirectX::SimpleMath::Matrix::Identity
		, GameContext<GameObjectManager>::Get()->GetCamera()->GetView(), GameContext<GameObjectManager>::Get()->GetCamera()->GetProjection());

	GameContext<GameObjectManager>::Get()->Render();
}

void PlayState::Finalize()
{
}
