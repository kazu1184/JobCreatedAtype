//======================================================
// File Name	: PlayState.h
// Summary		: プレイステイト
// Date			: 2019/011/19
// Author		: Kazuaki Hashimoto
//======================================================
#pragma once

#include "GameState.h"

#include "Model.h" 

class GameObjectManager;
class CollisionManager;
class Adx2Le;

class PlayState : public GameState
{
	private:

		// メンバ変数

		// オブジェクトマネージャー
		std::unique_ptr<GameObjectManager> m_objectManager;
		// コリジョンマネージャー
		std::unique_ptr<CollisionManager> m_collisionManager;
		//スカイドーム
		std::unique_ptr<DirectX::Model>   m_pSkyDoom;
		// オーディオ
		std::unique_ptr<Adx2Le> m_audio;

	public:

		// コンストラクタ・デストラクタ
		PlayState();
		virtual ~PlayState();

		// メンバ関数
		void Initialize() override;
		void Update() override;
		void Render() override;
		void Finalize() override;
};

