#include "pch.h"
#include "Player.h"

#include <Effects.h>
#include "DeviceResources.h"

#include "Transform.h"
#include "MapPosition.h"
#include "BoxCollider.h"
#include "RayCollider.h"
#include "GameContext.h"
#include "FollowCamera.h"
#include "GameObjectManager.h"
#include "CollisionManager.h"
#include "ModelMap.h"

#include "CharacterState.h"
#include "StandState.h"
#include "MoveState.h"
#include "KnockBackState.h"

#include "ADX2LE\Adx2Le.h"
#include "Resources\Audio\bgm_acf.h"

const float Player::CAMERA_DIRECTION = 2.0f;
const float Player::INITIALIZE_ANGLE = 90.0f;

Player::Player()
	: GameObject("Player")
	, m_angle(0.4f)
{
	// ���f���f�[�^�̓ǂݍ���
	DirectX::EffectFactory fx(GameContext<DX::DeviceResources>::Get()->GetD3DDevice());
	fx.SetDirectory(L"Resources\\Models");
	m_playerModel = DirectX::Model::CreateFromCMO(GameContext<DX::DeviceResources>::Get()->GetD3DDevice(), L"Resources\\Models\\humanoid.cmo", fx);

	// KeyboardStateTracker�I�u�W�F�N�g�𐶐����� 
	m_keyboardTracker = std::make_unique<DirectX::Keyboard::KeyboardStateTracker>();

	// �R���|�[�l���g�̒ǉ�
	m_transform = AddComponent<Transform>();
	m_transform->SetScale(DirectX::SimpleMath::Vector3(0.3f, 0.3f, 0.3f));
	m_transform->SetRotation(DirectX::SimpleMath::Vector3(0.f, 90.f, 0.f));

	m_playerMapPos = AddComponent<MapPosition>();
	m_playerMapPos->SetMapPosition(new MapPosition(1, 1));

	m_transform->SetPosition(DirectX::SimpleMath::Vector3(m_playerMapPos->GetX() * ModelMap::MAP_SIZE + ModelMap::MAP_SIZE / 2, 0, m_playerMapPos->GetY() * ModelMap::MAP_SIZE + ModelMap::MAP_SIZE / 2));

	// �����蔻��̒ǉ�
	BoxCollider* box = AddComponent<BoxCollider>();
	box->SetSize(DirectX::SimpleMath::Vector3(1.0f, 2.0f, 1.0f));
	GameContext<CollisionManager>::Get()->Add(GetTag(), box);

	// �X�e�C�g�̏�����
	m_standState = std::make_unique<StandState>();
	m_standState->Initialize(this);

	m_moveState = std::make_unique<MoveState>();
	m_moveState->Initialize(this);

	m_knockBackState = std::make_unique<KnockBackState>();
	m_knockBackState->Initialize(this);

	// �����X�e�C�g��stand�ɐݒ�
	ChangeState(m_standState.get());
}


Player::~Player()
{
	m_currentState->Finalize();
}

void Player::Update()
{
	// �R���|�[�l���g�̍X�V
	GameObject::Update();
	// �L�[�{�[�h�̏�Ԃ��擾����
	DirectX::Keyboard::State keyState = DirectX::Keyboard::Get().GetState();
	// �L�[�{�[�h�g���b�J�[���X�V����
	m_keyboardTracker->Update(keyState);
	// �X�e�C�g�̍X�V
	m_currentState->Update(m_keyboardTracker.get());
	// �J�����̍X�V
	CameraOperation(keyState);
	// ���L�����̃A���O���̍X�V
	m_transform->SetRotation(DirectX::SimpleMath::Vector3(0.0f, -m_angle + INITIALIZE_ANGLE, 0.0f));
}

void Player::Render()
{
	DX::DeviceResources* deviceResources = GameContext<DX::DeviceResources>::Get();
	FollowCamera* camera = GameContext<GameObjectManager>::Get()->GetCamera();
	// �v���C���[���f���̕`��
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
		// �m�b�N�o�b�N�X�e�C�g�ɐ؂�ւ���
		ChangeState(m_knockBackState.get());
	}
}

void Player::CameraOperation(DirectX::Keyboard::State key)
{
	// �J�����̍X�V
	FollowCamera* camera = GameContext<GameObjectManager>::Get()->GetCamera();
	camera->setRefTargetPos(m_transform->GetPosition());
	DirectX::Keyboard::State keyState = DirectX::Keyboard::Get().GetState();

	if (key.IsKeyDown(DirectX::Keyboard::Keys::Right))
	{
		// �J��������
		camera->RotateCamera(DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, 
			DirectX::XMConvertToRadians(m_direction == DIRECTION::BACKWARD ? +CAMERA_DIRECTION : -CAMERA_DIRECTION)), false);
		// �A���O���̍X�V
		m_direction == DIRECTION::BACKWARD ? m_angle -= CAMERA_DIRECTION : m_angle += CAMERA_DIRECTION;
	}

	if (key.IsKeyDown(DirectX::Keyboard::Keys::Left))
	{
		// �J��������
		camera->RotateCamera(DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY,
			DirectX::XMConvertToRadians(m_direction == DIRECTION::BACKWARD ? -CAMERA_DIRECTION : +CAMERA_DIRECTION)), false);
	    // �A���O���̍X�V
		m_direction == DIRECTION::BACKWARD ? m_angle += CAMERA_DIRECTION : m_angle -= CAMERA_DIRECTION;
	}

	camera->Update();
}
