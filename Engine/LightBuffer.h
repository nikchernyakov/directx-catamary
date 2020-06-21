#pragma once

#include "SimpleMath.h"

using namespace DirectX::SimpleMath;

struct LightBuffer
{
	Vector4 ambientColor;
	Vector4 diffuseColor;
	Vector3 lightDirection;
	float padding;  // Added extra padding so structure is a multiple of 16 for CreateBuffer function requirements.
};