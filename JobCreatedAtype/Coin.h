#pragma once
#include "GameObject.h"

#include <Model.h>

class Coin : public GameObject
{
	private:
		// ƒRƒCƒ“ƒ‚ƒfƒ‹
		std::unique_ptr<DirectX::Model> m_coinModel;

	public:
		Coin();
		~Coin();

		void Update()override;
		void Render()override;
		// “–‚½‚è”»’è
		void OnCollision(GameObject* object)override;
};

