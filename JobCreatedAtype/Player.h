//======================================================
// File Name	: Player.h
// Summary		: Playerクラス
// Date			: 2019/12/24
// Author		: Kazuaki Hashimoto
//======================================================
#pragma once
#include "GameObject.h"

#include <Model.h>
#include <Keyboard.h>

class RayCollider;

class CharacterState;
class StandState;
class MoveState;
class MapPosition;
class KnockBackState;

class Player : public GameObject
{
	public:
		// 移動状態
		enum DIRECTION
		{
			NONE,
			FORWARD,
			BACKWARD
		};
		// 定数
		static const float CAMERA_DIRECTION;
		static const float INITIALIZE_ANGLE;

	private:
		// プレイヤーモデル
		std::unique_ptr<DirectX::Model> m_playerModel;
		// カメラとプレイヤーの向いている角度
		float m_angle;
		// マップポジション
		MapPosition* m_playerMapPos;
		// 移動のステイト
		DIRECTION m_direction;
		// 現在の状態
		CharacterState* m_currentState;
		// ムーブ状態
		std::unique_ptr<MoveState> m_moveState;
		// 静止状態
		std::unique_ptr<StandState> m_standState;
		// ノックバック
		std::unique_ptr<KnockBackState> m_knockBackState;
		// キーボードトラッカー
		std::unique_ptr<DirectX::Keyboard::KeyboardStateTracker> m_keyboardTracker;
		
	public:
		// コンストラクタ・デストラクタ
		Player();
		~Player();

		void Update()override;
		void Render()override;
		// 当たり判定
		void OnCollision(GameObject* object)override;

		// 現在の状態を取得
		CharacterState* GetCurrentState() { return m_currentState; }
		// Stand状態を取得
		StandState* GetStand() { return m_standState.get(); }
		// Move状態を取得
		MoveState* GetMove() { return m_moveState.get(); }
		// ノックバック状態を取得
		KnockBackState* GetKnockBack() { return m_knockBackState.get(); }

		// 方向の取得
		DIRECTION GetDirection() { return m_direction; }
		// 方向のセット
		void SetDirection(DIRECTION dir) { m_direction = dir; }

		float GetAngle() { return m_angle; }

		MapPosition* GetMapPosition() { return m_playerMapPos; }

		// 状態遷移
		void ChangeState(CharacterState* state)
		{
			m_currentState = state;
		}

	private:
		void CameraOperation(DirectX::Keyboard::State key);
};

