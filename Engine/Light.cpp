#include "Game.h"
#include "Light.h"

Light::Light(Game* game, Vector3 position, Vector3 dir) : direction(dir)
{
	direction.Normalize();
	transform.setWorldPosition(position);
	
	projectionMatrix = Matrix::CreateOrthographic(
		120.0f, static_cast<float>(game->screenWidth) / static_cast<float>(game->screenHeight),
		0.1f, 100.0f);
}

Matrix Light::getViewMatrix()
{
	Vector3 up = { 0, 1, 0 };
	return Matrix::CreateLookAt(transform.getWorldPosition(), {0.0f, 0.0f, 0.0f}, up);
}

Matrix Light::getProjectionMatrix() const
{
	return projectionMatrix;
}

void Light::rotate(float dx, float dy)
{
	transform.addLocalRotation(Vector3::UnitY, dx * rotationSpeed);
	transform.addLocalRotation(Vector3::UnitX, dy * rotationSpeed);
}

void Light::translate(Vector3 translation)
{
	//transform.addWorldPosition(Vector3::Transform(translation, transform.m_Rotation));
	transform.addLocalPosition(translation);
}

void Light::update()
{
}
