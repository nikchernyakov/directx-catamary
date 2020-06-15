#pragma once

#include "Engine/PrimitiveGameObject.h"

class PyramidObject : public PrimitiveGameObject
{

public:
	PyramidObject(Game* game, Vector3 position, Vector4 color);

	void preDraw();
private:
	float m_rotateDelta;
};

