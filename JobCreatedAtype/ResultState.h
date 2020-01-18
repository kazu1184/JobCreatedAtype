//======================================================
// File Name	: ResultState.h
// Summary		: ���U���g�X�e�C�g
// Date			: 2019/01/19
// Author		: Kazuaki Hashimoto
//======================================================
#pragma once

#include "GameState.h"

class ResultState : public GameState
{
	private:
		// Debug�J�E���g
		int m_count;
	
	public:
		// �R���X�g���N�^�E�f�X�g���N�^
		ResultState();
		virtual ~ResultState();

		// �����o�֐�
		void Initialize() override;
		void Update() override;
		void Render() override;
		void Finalize() override;
};

