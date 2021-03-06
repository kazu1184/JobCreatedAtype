#include "pch.h"
#include "Player.h"

#include <Effects.h>
#include "DeviceResources.h"

#include "Transform.h"
#include "MapPosition.h"
#include "BoxCollider.h"
#include "GameContext.h"
#include "FollowCamera.h"
#include "GameObjectManager.h"
#include "CollisionManager.h"
#include "ModelMap.h"
#include "Coin.h"
#include "DrawingOff.h"

#include "CharacterState.h"
#include "StandState.h"
#include "MoveState.h"
#include "KnockBackState.h"

#include "ADX2LE\Adx2Le.h"
#include "Resources\Audio\bgm_acf.h"

#include "DebugFont.h"

const float Player::CAMERA_DIRECTION = 2.0f;
const float Player::INITIALIZE_ANGLE = 90.0f;

Player::Player()
	: GameObject("Player")
	, m_angle(0.4f)
	, m_coin(nullptr)
{
	// モデルデータの読み込み
	DirectX::EffectFactory fx(GameContext<DX::DeviceResources>::Get()->GetD3DDevice());
	fx.SetDirectory(L"Resources\\Models");
	m_playerModel = DirectX::Model::CreateFromCMO(GameContext<DX::DeviceResources>::Get()->GetD3DDevice(), L"Resources\\Models\\humanoid.cmo", fx);

	// KeyboardStateTrackerオブジェクトを生成する 
	m_keyboardTracker = std::make_unique<DirectX::Keyboard::KeyboardStateTracker>();
	
	// コンポーネントの追加
	m_transform = AddComponent<Transform>();
	m_transform->SetScale(DirectX::SimpleMath::Vector3(0.3f, 0.3f, 0.3f));

	m_playerMapPos = AddComponent<MapPosition>();
	m_playerMapPos->SetMapPosition(new MapPosition(11, 17));

	m_transform->SetPosition(DirectX::SimpleMath::Vector3(m_playerMapPos->GetX() * ModelMap::MAP_SIZE + ModelMap::MAP_SIZE / 2, 0, m_playerMapPos->GetY() * ModelMap::MAP_SIZE + ModelMap::MAP_SIZE / 2));

	// 描画範囲を管理するオブジェクトの追加
	std::unique_ptr<DrawingOff> drawOff = std::make_unique<DrawingOff>(this);
	GameContext<GameObjectManager>::Get()->Add(std::move(drawOff));

	// 当たり判定の追加
	BoxCollider* box = AddComponent<BoxCollider>();
	box->SetSize(DirectX::SimpleMath::Vector3(1.0f, 10.0f, 1.0f));
	box->SetOffset(DirectX::SimpleMath::Vector3(0.0f, 1.0f, 0.0f));
	GameContext<CollisionManager>::Get()->Add(GetTag(), box);

	// ステイトの初期化
	m_standState = std::make_unique<StandState>();
	m_standState->Initialize(this);

	m_moveState = std::make_unique<MoveState>();
	m_moveState->Initialize(this);

	m_knockBackState = std::make_unique<KnockBackState>();
	m_knockBackState->Initialize(this);

	// 初期ステイトをstandに設定
	ChangeState(m_standState.get());
}


Player::~Player()
{
	m_currentState->Finalize();
}

void Player::Update()
{
	if (!m_activeFlag)
		return;
	// コンポーネントの更新
	GameObject::Update();
	// キーボードの状態を取得する
	DirectX::Keyboard::State keyState = DirectX::Keyboard::Get().GetState();
	// キーボードトラッカーを更新する
	m_keyboardTracker->Update(keyState);
	if (m_currentState != nullptr)
		// ステイトの更新
		m_currentState->Update(m_keyboardTracker.get());
	// カメラの更新
	CameraOperation(keyState);
	// 自キャラのアングルの更新
	m_transform->SetRotation(DirectX::SimpleMath::Vector3(0.0f, -m_angle + INITIALIZE_ANGLE, 0.0f));
}

void Player::Render()
{
	if (!m_activeFlag)
		return;
	GameObject::Render();

	DX::DeviceResources* deviceResources = GameContext<DX::DeviceResources>::Get();
	FollowCamera* camera = GameContext<GameObjectManager>::Get()->GetCamera();
	// プレイヤーモデルの描画
	m_playerModel->Draw(deviceResources->GetD3DDeviceContext(),
		*GameContext<DirectX::CommonStates>::Get(),
		m_transform->GetWorld(), camera->GetView(), camera->GetProjection());
}

void Player::OnCollision(GameObject * object)
{
	if (object->GetTag() == "Floor")
	{
		m_playerMapPos->SetMapPosition(object->GetComponent<MapPosition>());
	}

	if (object->GetTag() == "Building")
	{
		GameContext<Adx2Le>::Get()->Play(CRI_BGM_ACF_AISACCONTROL_AISACCONTROL_04);
		// ノックバックステイトに切り替える
		ChangeState(m_knockBackState.get());
	}

	if (object->GetTag() == "Goal" && m_coin != nullptr)
	{
		m_currentState = nullptr;
	}
}

void Player::CameraOperation(DirectX::Keyboard::State key)
{
	// カメラの更新
	FollowCamera* camera = GameContext<GameObjectManager>::Get()->GetCamera();
	camera->setRefTargetPos(m_transform->GetPosition());
	DirectX::Keyboard::State keyState = DirectX::Keyboard::Get().GetState();

	if (key.IsKeyDown(DirectX::Keyboard::Keys::Right))
	{
		// カメラを回す
		camera->RotateCamera(DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, 
			DirectX::XMConvertToRadians(m_direction == DIRECTION::BACKWARD ? +CAMERA_DIRECTION : -CAMERA_DIRECTION)), false);
		// アングルの更新
		m_direction == DIRECTION::BACKWARD ? m_angle -= CAMERA_DIRECTION : m_angle += CAMERA_DIRECTION;
	}

	if (key.IsKeyDown(DirectX::Keyboard::Keys::Left))
	{
		// カメラを回す
		camera->RotateCamera(DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY,
			DirectX::XMConvertToRadians(m_direction == DIRECTION::BACKWARD ? -CAMERA_DIRECTION : +CAMERA_DIRECTION)), false);
	    // アングルの更新
		m_direction == DIRECTION::BACKWARD ? m_angle += CAMERA_DIRECTION : m_angle -= CAMERA_DIRECTION;
	}
	camera->Update();
}
