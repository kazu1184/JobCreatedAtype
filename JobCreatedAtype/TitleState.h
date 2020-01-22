//======================================================
// File Name	: TitleState.h
// Summary		: �^�C�g���X�e�C�g
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

		// �R���X�g���N�^�E�f�X�g���N�^
		TitleState();
		virtual ~TitleState();

		// �����o�֐�
		void Initialize() override;
		void Update() override;
		void Render() override;
		void Finalize() override;
};

