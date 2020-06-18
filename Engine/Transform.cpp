#include "Transform.h"

Transform::Transform(Vector3 pos)
{
	setPosition(pos);
}

Transform& Transform::getParent() const
{
	return *parent;
}

std::vector<std::shared_ptr<Transform>>& Transform::getChild()
{
	return children;
}

void Transform::addChild(Transform* obj)
{
	children.push_back(std::unique_ptr<Transform>(obj));
	obj->parent = std::unique_ptr<Transform>(this);
	updateWorldMatrix();
}

void Transform::setParent(Transform* p)
{
	parent = std::unique_ptr<Transform>(p);
	p->children.push_back(std::unique_ptr<Transform>(this));
	updateWorldMatrix();
}

Vector3 Transform::getPosition() const
{
	return m_position;
}

Vector3 Transform::getWorldPosition() const
{
	return m_world.Translation();
}

void Transform::setPosition(Vector3 pos)
{
	m_position = pos;
	updateWorldMatrix();
}

void Transform::addPosition(Vector3 pos)
{
	m_position += pos;
	updateWorldMatrix();
}

void Transform::addLocalRotation(Vector3 axis, const float angle)
{
	/*m_eulerAngles += axis * angle;
	rotation = Quaternion::CreateFromYawPitchRoll(m_eulerAngles.y, m_eulerAngles.x, m_eulerAngles.z);*/

	rotation = Quaternion::CreateFromRotationMatrix(Matrix::CreateFromAxisAngle(axis, angle) * m_world);
	updateWorldMatrix();
}

void Transform::updateWorldMatrix()
{
	m_world = Matrix::CreateFromQuaternion(rotation) * Matrix::CreateTranslation(m_position);
	
	if (parent)
	{
		m_world *= parent->getWorldMatrix();
	}

	for (const std::shared_ptr<Transform>& element : children)
	{
		element->updateWorldMatrix();
	}
}

Matrix Transform::getWorldMatrix() const
{
	return m_world;
}
