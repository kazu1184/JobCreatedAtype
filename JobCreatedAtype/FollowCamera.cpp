//======================================================
// File Name	: FollowCamera.cpp
// Summary		: カメラ
// Date			: 2019/05/31
// Author		: Kazuaki Hashimoto
//======================================================

#include "pch.h"
#include "FollowCamera.h"

#include <SimpleMath.h>
#include "DeviceResources.h"
#include "DebugFont.h"

#include "GameContext.h"
#include "CollisionManager.h"
#include "SphereCollider.h"
#include "Transform.h"

//定数の定義
const DirectX::SimpleMath::Vector3 FollowCamera::TARGET_TO_EYE_VEC(0.0f, 5.0f, 10.0f);  //カメラの距離
const float FollowCamera::TIME_TO_TURN = 0.3f;                                          //保管して回る時間
const float FollowCamera::TIME_TO_DELAY = 0.05f;                                        //カメラを遅らせる時間

// コンストラクタ
FollowCamera::FollowCamera(DirectX::SimpleMath::Vector3 target)
	: m_target(target)
{
	RECT size = GameContext<DX::DeviceResources>::Get()->GetOutputSize();
	float aspectRatio = float(size.right) / float(size.bottom);

	// 画角を設定
	float fovAngleY = DirectX::XMConvertToRadians(45.0f);

	// プロジェクション行列計算・設定
	m_projection = DirectX::SimpleMath::Matrix::CreatePerspectiveFieldOfView(
		fovAngleY,
		aspectRatio,
		0.01f,
		10000.0f);
}
// デストラクタ
FollowCamera::~FollowCamera()
{

}

// 更新
void FollowCamera::Update()
{
	// カメラの角度の設定
	DirectX::SimpleMath::Vector3 up(0.0f, 1.0f, 0.0f);

	// ゴム紐追従
	m_target += (m_refTargetPos - m_target) * TIME_TO_DELAY;

	// Laap
	m_rotation = DirectX::SimpleMath::Quaternion::Slerp(m_rotation, m_refRotation, TIME_TO_TURN);

	// Eyeの更新
	m_eye = DirectX::SimpleMath::Vector3::Transform(TARGET_TO_EYE_VEC, m_rotation);

	// Viewの決定
	m_view = DirectX::SimpleMath::Matrix::CreateLookAt(m_target + m_eye, m_target, up);
}

// カメラの回転
void FollowCamera::RotateCamera(const DirectX::SimpleMath::Quaternion& rotation, bool immediately)
{
	// 回転の更新
	m_refRotation *= rotation;

	// trueならば保管をやめる
	if (immediately)
		m_rotation = m_refRotation;
}
