#pragma once
#include "Engine/ModelObject.h"
#include <string>
#include <DirectXCollision.h>
class Game;

class KatamariSphere : public ModelObject
{
public:
	KatamariSphere(Game* game, const std::string& filePath, const wchar_t* texturePath);

	DirectX::BoundingSphere collider;
};

