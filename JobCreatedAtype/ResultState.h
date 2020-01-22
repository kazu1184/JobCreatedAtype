//======================================================
// File Name	: ResultState.h
// Summary		: リザルトステイト
// Date			: 2019/01/19
// Author		: Kazuaki Hashimoto
//======================================================
#pragma once

#include "GameState.h"

#include "SpriteBatch.h"

class ResultState : public GameState
{
	private:
		// Debugカウント
		int m_count;
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_resultTexture;

	public:
		// コンストラクタ・デストラクタ
		ResultState();
		virtual ~ResultState();

		// メンバ関数
		void Initialize() override;
		void Update() override;
		void Render() override;
		void Finalize() override;
};

