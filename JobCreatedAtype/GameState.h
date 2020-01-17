//======================================================
// File Name	: GameState.h
// Summary		: ステイト(純粋仮想クラス)
// Date			: 2019/011/19
// Author		: Kazuaki Hashimoto
//======================================================
#pragma once

class GameState
{
	public: 

		// コンストラクタ・デストラクタ
		GameState() = default;
		virtual ~GameState() = default;

		// メンバ関数
		virtual void Initialize() = 0;
		virtual void Update() = 0;
		virtual void Render() = 0;
		virtual void Finalize() = 0;
};