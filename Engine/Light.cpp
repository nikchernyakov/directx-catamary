#include "Game.h"
#include "Light.h"

Light::Light(Game* game, Vector3 position, Vector3 direction) : direction(direction)
{
	transform.setWorldPosition(position);

	projectionMatrix = Matrix::CreatePerspectiveFieldOfView(
		DirectX::XM_PIDIV2, 1.0f, 1.0f, 100.0f);
}

Matrix Camera::getViewMatrix()
{
	Vector3 target = Vector3::Transform(direction, transform.getWorldMatrix());
	Vector3 up = { 0, 1, 0 };
	return Matrix::CreateLookAt(transform.getWorldPosition(), target, up);
}

Matrix Camera::getProjectionMatrix() const
{
	return projectionMatrix;
}

void Camera::rotate(float dx, float dy)
{
	transform.addLocalRotation(Vector3::UnitY, dx * rotationSpeed);
	transform.addLocalRotation(Vector3::UnitX, dy * rotationSpeed);
}

void Camera::translate(Vector3 translation)
{
	//transform.addWorldPosition(Vector3::Transform(translation, transform.m_Rotation));
	transform.addLocalPosition(translation);
}

void Camera::update()
{
}
