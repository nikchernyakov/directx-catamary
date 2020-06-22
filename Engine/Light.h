#pragma once

#include "Transform.h"

class Game;
using namespace DirectX::SimpleMath;

class Light
{
public:
	Light(Game* game, Vector3 position, Vector3 direction = {0, 0, 1});
	~Light() = default;

	Matrix getViewMatrix();
	Matrix getProjectionMatrix() const;

	void rotate(float dx, float dy);
	void translate(Vector3 translation);
	virtual void update();
	
	Transform transform;
	Vector3 direction;
	
protected:

	float rotationSpeed = 0.1;
	float moveSpeed = 5;
	
	Matrix projectionMatrix;
	
};

