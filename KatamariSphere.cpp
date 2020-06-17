#include "KatamariSphere.h"

KatamariSphere::KatamariSphere(Game* game, const std::string& filePath, Shader* shader)
  : ModelObject(game, filePath, shader)
{
	collider = DirectX::BoundingSphere({ 0, 0, 0 }, 1);
}
