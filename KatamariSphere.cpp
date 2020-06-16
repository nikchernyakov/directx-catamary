#include "KatamariSphere.h"

KatamariSphere::KatamariSphere(Game* game, const std::string& filePath, const wchar_t* texturePath)
  : ModelObject(game, filePath, texturePath)
{
	collider = DirectX::BoundingSphere({ 0, 0, 0 }, 1);
}
