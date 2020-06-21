#include "Transform.h"

Transform::Transform(Vector3 pos)
{
	m_world = Matrix::CreateFromQuaternion(Quaternion::Identity) * Matrix::CreateTranslation(pos);
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
	obj->m_world *= getWorldMatrix().Invert();
}

void Transform::setParent(Transform* p)
{
	parent = std::unique_ptr<Transform>(p);
	p->children.push_back(std::unique_ptr<Transform>(this));
	m_world *= p->getWorldMatrix().Invert();
}

Vector3 Transform::getPosition() const
{
	return m_Translation.Translation();
}

Vector3 Transform::getWorldPosition() const
{
	return getWorldMatrix().Translation();
}

void Transform::setPosition(Vector3 pos)
{
	m_world = getWorldMatrix() * m_Translation.Invert();
	m_Translation = Matrix::CreateTranslation(pos);
	m_world *= m_Translation;
}

void Transform::addPosition(Vector3 pos)
{
	m_world = getWorldMatrix() * Matrix::CreateTranslation(pos);
	m_Translation *= Matrix::CreateTranslation(pos);
}

void Transform::addLocalRotation(Vector3 axis, const float angle)
{
	m_Rotation *= Matrix::CreateFromAxisAngle(axis, angle);
	m_world = getWorldMatrix() * m_Translation.Invert() * Matrix::CreateFromAxisAngle(axis, angle) * m_Translation;
}

Matrix Transform::getWorldMatrix() const
{
	auto result = m_world;

	if (parent)
	{
		result *= parent->getWorldMatrix();
	}
	
	return result;
}
