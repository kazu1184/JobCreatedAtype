#pragma once
#include "Component.h"

class MapPosition : public Component
{
	private:
		int m_x;
		int m_y;

	public:
		// コンストラクタ・デストラクタ
		MapPosition();
		~MapPosition();

		// メンバ関数
		void Initialize()override;
		void Update()override;

		int GetX() { return m_x; }
		int GetY() { return m_y; }

		void SetX(int x) { m_x = x; }
		void SetY(int y) { m_y = y; }

		void SetMapPosition(int x, int y)
		{
			m_x = x;
			m_y = y;
		}

		void SetMapPosition(MapPosition* pos)
		{
			m_x = pos->GetX();
			m_y = pos->GetY();
		}
};

