#include "Transform.h"

Transform::Transform(Vector3 pos) : m_position(pos)
{
}

Transform& Transform::getParent() const
{
	return *parent;
}

std::vector<std::shared_ptr<Transform>>& Transform::getChild()
{
	return child;
}

void Transform::addChild(Transform* obj)
{
	child.push_back(std::unique_ptr<Transform>(obj));
}

void Transform::setParent(Transform* p)
{
	parent = std::unique_ptr<Transform>(p);
}

Vector3 Transform::getPosition()
{
	return m_position;
}

void Transform::setPosition(Vector3 pos)
{
	m_position = pos;
}

void Transform::addPosition(Vector3 pos)
{
	m_position += pos;
}

void Transform::rotate(const Vector3 axis, const float angle)
{
	m_eulerAngles = Vector3 { axis.x * angle + m_eulerAngles.x, axis.y * angle + m_eulerAngles.y, axis.z * angle + m_eulerAngles.z };
	rotation = Quaternion::CreateFromYawPitchRoll(m_eulerAngles.y, m_eulerAngles.x, m_eulerAngles.z);
}

Matrix Transform::CreateWorldMatrix() const
{
	Matrix mat = Matrix::CreateFromQuaternion(rotation) * Matrix::CreateTranslation(m_position);
	
	if (parent)
	{
		mat *= parent->CreateWorldMatrix();
	}

	return mat;
}
