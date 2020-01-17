//======================================================
// File Name	: GameState.h
// Summary		: ステイト(純粋仮想クラス)
// Date			: 2019/011/19
// Author		: Kazuaki Hashimoto
//======================================================
#pragma once
// インクルード
#include <functional>
#include <memory>
#include <deque>
#include <string>
#include <unordered_map>

// 前方宣言
class GameState;

class GameStateManager final
{
	// using

	private:
		// シーンのスタック
		using GameStateStack = std::deque<std::unique_ptr<GameState>>;
		// 関数オブジェクト
		using GameStateFactory = std::function<std::unique_ptr<GameState>()>;
		// 関数オブジェクトの登録
		using GameStateFactoryList = std::unordered_map<std::string, GameStateFactory>;

	// メンバ変数

		// 関数の配列(コンテナ)
		GameStateFactoryList m_stateFactories;
		// 現在のステイト
		GameStateStack       m_states;
		// ポップカウント
		int                  m_popCount;
		// 次のシーンの名前
		std::string          m_nextStateName;

	// メンバ関数（プライベート）

		// ステイトの生成
		template<typename State>
		static std::unique_ptr<GameState> CreateState();

		// ステイトの変更
		void ChangeState();

	// コンストラクタ・デストラクタ
	public:
		GameStateManager();
		~GameStateManager();

	// メンバ関数（パブリック）
		
		// ステイトの登録
		template<typename State>
		void RegisterState(const std::string& stateName);
		// 更新
		void Update(float elapsedTime);
		// 描画
		void Render();
		// ステイトのリクエスト
		void RequestState(const std::string& stateName);
		// ステイトのプッシュ
		void PushState(const std::string& stateName);
		// ステイトのポップ
		void PopState(int count = 1);
};

template<typename State>
inline std::unique_ptr<GameState> GameStateManager::CreateState()
{
	return std::make_unique<State>();
}

template<typename State>
inline void GameStateManager::RegisterState(const std::string & stateName)
{
	m_stateFactories.insert(std::make_pair(stateName, CreateState<State>));
}
