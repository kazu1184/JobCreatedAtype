//======================================================
// File Name	: TitleState.h
// Summary		: �^�C�g���X�e�C�g
// Date			: 2019/011/19
// Author		: Kazuaki Hashimoto
//======================================================
#pragma once

#include "GameState.h"

class TitleState : public GameState
{
	private: 

		// Debug�J�E���g
		int m_count;

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

