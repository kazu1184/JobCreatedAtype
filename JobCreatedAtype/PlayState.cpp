//======================================================
// File Name	: PlayState.cpp
// Summary		: �v���C�X�e�C�g
// Date			: 2019/011/19
// Author		: Kazuaki Hashimoto
//======================================================

#include "pch.h"

#include <Keyboard.h>

#include "PlayState.h"
#include "DebugFont.h"
#include "GameContext.h"
#include "Player.h"
#include "Enemy.h"
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
	// �I�u�W�F�N�g�}�l�[�W���[�����E�o�^
	m_objectManager = std::make_unique<GameObjectManager>();
	GameContext<GameObjectManager>::Register(m_objectManager);
	// �R���W�����}�l�W���[
	m_collisionManager = std::make_unique<CollisionManager>();
	m_collisionManager->AllowCollision("Player", "Floor");
	m_collisionManager->AllowCollision("Building", "Player");
	GameContext<CollisionManager>::Register(m_collisionManager);
	// �}�b�v�̐����E�o�^
	std::unique_ptr<ModelMap> map = std::make_unique<ModelMap>();
	m_objectManager->Add(std::move(map));
	// �v���C���[�E�G�l�~�[�̓o�^
	std::unique_ptr<Player> player = std::make_unique<Player>();
	std::unique_ptr<Enemy> enemy = std::make_unique<Enemy>(player.get());
	m_objectManager->Add(std::move(player));
	m_objectManager->Add(std::move(enemy));

	DirectX::EffectFactory* factory = new DirectX::EffectFactory(GameContext<DX::DeviceResources>::Get()->GetD3DDevice());
	// �e�N�X�`���̓ǂݍ��݃p�X�w�� 
	factory->SetDirectory(L"Resources/Models");
	// �V��
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
