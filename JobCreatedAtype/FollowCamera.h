//======================================================
// File Name	: FollowCamera.h
// Summary		: カメラ
// Date			: 2019/05/31
// Author		: Kazuaki Hashimoto
//======================================================
#pragma once
#include "SimpleMath.h"

class RayCollider;

class FollowCamera 
{
	public: //メンバ定数

		//カメラの距離
		static const DirectX::SimpleMath::Vector3 TARGET_TO_EYE_VEC;

	private: //メンバ定数

		//保管して回る時間
		static const float TIME_TO_TURN;
		//カメラを遅らせる時間
		static const float TIME_TO_DELAY;

	private: //メンバ変数

		// 生成されたビュー行列
		DirectX::SimpleMath::Matrix m_view;
		// プロジェクション
		DirectX::SimpleMath::Matrix m_projection;
		// 注視点
		DirectX::SimpleMath::Vector3 m_target;
		DirectX::SimpleMath::Vector3 m_eye;
		// 参照注視点 
		DirectX::SimpleMath::Vector3 m_refTargetPos;
		// 回転
		DirectX::SimpleMath::Quaternion m_rotation;
		// 保管用回転
		DirectX::SimpleMath::Quaternion m_refRotation;
		// Ray
		RayCollider* m_ray;
	
	
	public: // コンストラクタ・デストラクタ
		
		FollowCamera(DirectX::SimpleMath::Vector3 target);
		~FollowCamera();
	
	public: //メンバ関数

		void Update();
		void RotateCamera(const DirectX::SimpleMath::Quaternion& rotation, bool immediately = false);
	
	public: //アクセッサ

		// 参照注視点
		DirectX::SimpleMath::Vector3 getRefTargetPos(){ return m_refTargetPos; }
		void setRefTargetPos(const DirectX::SimpleMath::Vector3& ref){ m_refTargetPos = ref; }
	
		DirectX::SimpleMath::Vector3 getEye() { return m_eye; }

		// ビュー行列取得
		const DirectX::SimpleMath::Matrix& GetView(){ return m_view; }

		// プロジェクション行列取得
		const DirectX::SimpleMath::Matrix& GetProjection() { return m_projection; }
	
		// 保管用回転取得
		DirectX::SimpleMath::Quaternion GetRotation(){ return m_refRotation; }

		// 回転セット
		void SetRotation(const DirectX::SimpleMath::Quaternion& angle,bool immediately = false)
		{
			m_refRotation = angle;

			if (immediately)
				m_rotation = m_refRotation;
		}
};