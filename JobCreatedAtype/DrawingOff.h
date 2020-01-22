#pragma once
#include "GameObject.h"

#include "PrimitiveBatch.h"
#include "CommonStates.h"
#include "VertexTypes.h"

class RayCollider;
class Player;

class DrawingOff : public GameObject
{
	public:
		// �`��͈�
		static const float DROW_LENGTH;
	private:
		// �f�o�b�N�`��p
		std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColor>> m_pLinePrimitiveBatch;
		// ���C
		RayCollider* m_ray;
		// �v���C���[�̃|�C���^
		Player* m_player;

	public:
		DrawingOff(Player* player);
		~DrawingOff();

		void Update()override;
		void Render()override;
		// �����蔻��
		void OnCollision(GameObject* object)override;
};

