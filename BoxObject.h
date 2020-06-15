#pragma once

#include "Engine/PrimitiveGameObject.h"

class BoxObject : public PrimitiveGameObject
{

public:
	BoxObject(Game* game, Vector3 position, Vector4 color, Vector3 boxSize);
};

