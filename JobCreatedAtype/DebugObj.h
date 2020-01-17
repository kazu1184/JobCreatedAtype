#pragma once
#include "GameObject.h"
#include <GeometricPrimitive.h>
#include <SimpleMath.h>

class Transform;

class DebugObj : public GameObject
{
	std::unique_ptr<DirectX::GeometricPrimitive> m_box;
	std::unique_ptr<Transform> m_transform;
	bool flag;

public:
	DebugObj();
	~DebugObj();

	void Update()override;
	void Render()override;

	void OnCollision(GameObject * object)override;
};

