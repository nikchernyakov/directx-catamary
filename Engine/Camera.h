#pragma once

#include "Libraries/SimpleMath/SimpleMath.h"
#include "Transform.h"

class Game;
using namespace DirectX::SimpleMath;

class Camera
{
public:
	Camera(Game* game, Vector3 position, Vector3 direction = {0, 0, 1});
	~Camera() = default;

	Matrix getViewMatrix();
	Matrix getProjectionMatrix() const;

	void rotate(float dx, float dy);
	void translate(Vector3 translation);

private:
	Transform transform;

	Vector3 direction;

	float rotationSpeed = 0.001;
	float moveSpeed = 5;
	
	Matrix projectionMatrix;
	
};

