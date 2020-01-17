#pragma once
#include "GameObject.h"

#include <Model.h>

class CharacterState;
class MapPosition;
class Player;

class Enemy : public GameObject
{
	private:
		// エネミーモデル
		std::unique_ptr<DirectX::Model> m_enemyModel;
		// ターゲットポインタ
		Player* m_target;
		//// 開始位置
		//MapPosition m_startPosition;
		//// 終了位置
		//MapPosition m_endPosition;
		//// 最短経路
		//std::vector<MapPosition> m_route;
		//// 移動行列
		//DirectX::SimpleMath::Matrix m_translation;

		// 現在の状態
		CharacterState* m_currentState;

	public:
		Enemy(Player* player);
		~Enemy();

		void Update()override;
		void Render()override;
		// 当たり判定
		virtual void OnCollision(GameObject* object)override;

		// 現在の状態を取得
		CharacterState* GetCurrentState() { return m_currentState; }

		// 状態遷移
		void ChangeState(CharacterState* state){ m_currentState = state; }

		//// 開始位置を取得する
		//MapPosition GetStartPosition()
		//{
		//	return m_startPosition;
		//}
		//// 開始位置を設定する
		//void SetStartPosition(const MapPosition& startPosition)
		//{
		//	m_startPosition = startPosition;
		//}
		//// 終了位置を取得する
		//MapPosition GetEndPosition()
		//{
		//	return m_endPosition;
		//}
		//// 終了位置を設定する
		//void SetEndPosition(const MapPosition& endPosition)
		//{
		//	m_endPosition = endPosition;
		//}

		//// 最短経路を取得する
		//std::vector<MapPosition> GetRoute()
		//{
		//	return m_route;
		//}

};

