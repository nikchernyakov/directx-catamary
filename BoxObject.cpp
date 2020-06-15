#include "Engine/Game.h"
#include "BoxObject.h"
#include "Engine/ConstantBuffer.h"

BoxObject::BoxObject(Game* game, Vector3 position, Vector4 color, float boxSize, float boxSpeed)
	: PrimitiveGameObject(game, position), m_boxSize(boxSize), m_boxSpeed(boxSpeed)
{
	m_vertices =
	{
		// Top vertices
		{
			{-boxSize, -boxSize, -boxSize}, color
		},
		{
			{-boxSize, +boxSize, -boxSize}, color
		},
		{
			{+boxSize, +boxSize, -boxSize}, color
		},
		{
			{ +boxSize, -boxSize, -boxSize}, color
		},
		// Bottom vertices
		{
			{-boxSize, -boxSize, +boxSize}, color
		},
		{
			{-boxSize, +boxSize, +boxSize}, color
		},
		{
			{+boxSize, +boxSize, +boxSize}, color
		},
		{
			{+boxSize, -boxSize, +boxSize}, color
		}
	};

	m_indices =
	{
		// front face
		0, 1, 2,
		0, 2, 3,

		// back face
		4, 6, 5,
		4, 7, 6,

		// left face
		4, 5, 1,
		4, 1, 0,

		// right face
		3, 2, 6,
		3, 6, 7,

		// top face
		1, 5, 6,
		1, 6, 2,

		// bottom face
		4, 0, 3,
		4, 3, 7
	};

	PrimitiveGameObject::init();
}

void BoxObject::preDraw()
{
	m_rotateDelta += static_cast<float>(DirectX::XM_PI) * m_game->deltaTime * m_boxSpeed;
	transform->rotate(Vector3::UnitY, m_rotateDelta);
}
