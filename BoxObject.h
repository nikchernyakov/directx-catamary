#pragma once

#include "Engine/PrimitiveGameObject.h"

class BoxObject : public PrimitiveGameObject
{

public:
	BoxObject(Game* game, Vector3 position, Vector4 color, float boxSize, float boxSpeed);

	void preDraw();
private:
	float m_boxSize = 1;
	float m_boxSpeed = 1;
	float m_rotateDelta = 0;
};

