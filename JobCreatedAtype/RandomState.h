#pragma once
#include "CharacterState.h"

class Enemy;
class ModelMap;
class MapPosition;

class RandomState : public CharacterState
{
	public:
		// 思考時間
		static const int THINKING_INTERVAL;

	private: 
		// エネミー
		Enemy* m_enemy;
		// 速度
		DirectX::SimpleMath::Vector3 m_velocity;
		// エネミーのマップポジション
		MapPosition* m_currentMapPos;
		// 方向
		int m_direction;
		// 時間
		int m_count;
		// マップポインタ
		ModelMap* m_map;
	
	public:
		// コンストラクタ
		RandomState();

		// 初期化する
		bool Initialize(GameObject* object)override;
		// 更新する
		bool Update(DirectX::Keyboard::KeyboardStateTracker* keyboard = nullptr)override;
		// 後始末をする
		bool Finalize()override;

	private:
		// フロートを比べる
		inline bool FloatEquals(float a, float b)
		{
			if (std::abs(a - b) <= std::numeric_limits<float>::epsilon())
			{
				return true;
			}
			else
			{
				return false;
			}
		}
};

