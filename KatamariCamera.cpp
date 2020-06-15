#include "Engine/Game.h"
#include "KatamariCamera.h"

KatamariCamera::KatamariCamera(Game* game, Vector3 position, GameObject* observedObject)
	: Camera(game, position), m_observedObject(observedObject), m_offset(position)
{
}

void KatamariCamera::update()
{
	transform.setPosition(m_observedObject->transform->getPosition() + m_offset);
}
