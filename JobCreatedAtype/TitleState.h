//======================================================
// File Name	: TitleState.h
// Summary		: タイトルステイト
// Date			: 2019/011/19
// Author		: Kazuaki Hashimoto
//======================================================
#pragma once

#include "GameState.h"

#include "SpriteBatch.h"

class TitleState : public GameState
{
	private: 
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_resultTexture;

	public:

		// コンストラクタ・デストラクタ
		TitleState();
		virtual ~TitleState();

		// メンバ関数
		void Initialize() override;
		void Update() override;
		void Render() override;
		void Finalize() override;
};

