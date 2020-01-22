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
		// 描画範囲
		static const float DROW_LENGTH;
	private:
		// デバック描画用
		std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColor>> m_pLinePrimitiveBatch;
		// レイ
		RayCollider* m_ray;
		// プレイヤーのポインタ
		Player* m_player;

	public:
		DrawingOff(Player* player);
		~DrawingOff();

		void Update()override;
		void Render()override;
		// 当たり判定
		void OnCollision(GameObject* object)override;
};

