#pragma once
#include "GameObject.h"

#include <Model.h>

class CharacterState;
class Idling;
class Chasing;
class Searching;
class MapPosition;
class Player;

class Enemy : public GameObject
{
	private:
		// エネミーモデル
		std::unique_ptr<DirectX::Model> m_enemyModel;
		// ターゲットポインタ
		Player* m_target;
		// 開始位置
		MapPosition* m_startPosition;
		// 終了位置
		MapPosition* m_endPosition;
		// 最短経路
		std::vector<MapPosition*> m_route;
		// 移動行列
		DirectX::SimpleMath::Matrix m_translation;

		// 現在の状態
		CharacterState* m_currentState;
		// アイドル状態
		std::unique_ptr<Idling> m_idlingState;
		// 探索状態
		std::unique_ptr<Searching> m_searchingState;
		// 追跡状態
		std::unique_ptr<Chasing> m_chasingState;

	public:
		Enemy(Player* player);
		~Enemy();

		void Update()override;
		void Render()override;
		// 当たり判定
		virtual void OnCollision(GameObject* object)override;

		// 現在の状態を取得
		CharacterState* GetCurrentState() { return m_currentState; }

		// Idling状態を取得する
		Idling* GetIdlingState() const
		{
			return m_idlingState.get();
		}

		// Searching状態を取得する
		Searching* GetSearchingState() const
		{
			return m_searchingState.get();
		}

		// Chasing状態を取得する
		Chasing* GetChasingState() const
		{
			return m_chasingState.get();
		}

		// 状態遷移
		void ChangeState(CharacterState* state){ m_currentState = state; }

		// 開始位置を取得する
		MapPosition* GetStartPosition()
		{
			return m_startPosition;
		}
		// 開始位置を設定する
		void SetStartPosition(MapPosition* startPosition)
		{
			m_startPosition = startPosition;
		}
		// 終了位置を取得する
		MapPosition* GetEndPosition()
		{
			return m_endPosition;
		}
		// 終了位置を設定する
		void SetEndPosition(MapPosition* endPosition)
		{
			m_endPosition = endPosition;
		}

		// 最短経路を取得する
		std::vector<MapPosition*> GetRoute()
		{
			return m_route;
		}

};

