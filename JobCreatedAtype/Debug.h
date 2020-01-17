#pragma once

#include "GameObject.h"
#include <GeometricPrimitive.h>
#include <SimpleMath.h>

class Transform;

class Debug : public GameObject
{
	std::unique_ptr<DirectX::GeometricPrimitive> m_box;
	std::unique_ptr<Transform> m_transform;
	bool flag;

public:
	Debug();
	~Debug();

	void Update()override;
	void Render()override;

	void OnCollision(GameObject * object)override;
};

