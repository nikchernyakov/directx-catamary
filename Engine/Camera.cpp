#include "Game.h"
#include "Camera.h"
#include "GameMath.h"

Camera::Camera(Game* game, Vector3 position, Vector3 direction) : direction(direction)
{
	transform.setPosition(position);
	
	projectionMatrix = Matrix::CreatePerspectiveFieldOfView(
		120, static_cast<float>(game->screenWidth) / static_cast<float>(game->screenHeight),
		0.01f, 100.0f);
}

Matrix Camera::getViewMatrix()
{
	Vector3 target = { direction };
	Vector3::Transform(direction,
		Matrix::CreateFromQuaternion(transform.rotation),
		target);
	target += transform.getPosition();
	Vector3 up = { 0, 1, 0 };
	return Matrix::CreateLookAt(transform.getPosition(), target, up);
}

Matrix Camera::getProjectionMatrix() const
{
	return projectionMatrix;
}

void Camera::rotate(float dx, float dy)
{
	transform.rotation += Quaternion::CreateFromYawPitchRoll(dx * rotationSpeed, dy * rotationSpeed, 0);
}

void Camera::translate(Vector3 translation)
{
	XMStoreFloat3(&translation, DirectX::XMVector3Transform(
		DirectX::XMLoadFloat3(&translation),
		Matrix::CreateFromQuaternion(transform.rotation) *
		DirectX::XMMatrixScaling(moveSpeed, moveSpeed, moveSpeed)
	));
	transform.addPosition({
		translation.x,
		translation.y,
		translation.z
		}
	);
}

void Camera::update()
{
}
