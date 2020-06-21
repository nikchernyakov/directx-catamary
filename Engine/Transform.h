#pragma once

#include <d3d11.h>
#include "SimpleMath.h"

using namespace DirectX::SimpleMath;

struct Transform
{
public:
	Transform() = default;
	Transform(Vector3 pos);
	~Transform() = default;

	Transform& getParent() const;
	std::vector<std::shared_ptr<Transform>>& getChild();
	void addChild(Transform* obj);
	void setParent(Transform* parent);

	Vector3 getPosition() const;
	Vector3 getWorldPosition() const;
	void setPosition(Vector3 pos);
	void addPosition(Vector3 pos);

	std::unique_ptr<Transform> parent = nullptr;
	std::vector<std::shared_ptr<Transform>> children;

	void addLocalRotation(Vector3 axis, float angle);

	Matrix getWorldMatrix() const;
	Matrix m_world = Matrix::Identity;
	Matrix m_Translation = Matrix::Identity;
	Matrix m_Rotation = Matrix::Identity;
	Matrix m_Scale = Matrix::Identity;
};

