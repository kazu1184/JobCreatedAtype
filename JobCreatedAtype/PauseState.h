//======================================================
// File Name	: PauseState.h
// Summary		: �|�[�Y�X�e�C�g
// Date			: 2019/011/19
// Author		: Kazuaki Hashimoto
//======================================================
#pragma once

#include "GameState.h"

class PauseState :public GameState
{
	public:

		// �R���X�g���N�^�E�f�X�g���N�^
		PauseState();
		virtual ~PauseState();
	
		// �����o�֐�
		void Initialize() override;
		void Update() override;
		void Render() override;
		void Finalize() override;
};

