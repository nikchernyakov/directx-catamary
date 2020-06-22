#pragma once

#include "SimpleMath.h"

using namespace DirectX::SimpleMath;

struct LightBuffer
{
	Vector4 ambientColor;
	Vector4 diffuseColor;
	Vector3 lightPosition;
	Vector3 lightDirection;
	float specularPower;
	Vector4 specularColor;
	float lightPadding = 0.0f;
};