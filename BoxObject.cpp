#include "Engine/Game.h"
#include "BoxObject.h"
#include "Engine/ConstantBuffer.h"

BoxObject::BoxObject(Game* game, Shader* shader, Vector3 position, Vector4 color, Vector3 boxSize)
	: RenderedGameObject(game, shader, position)
{
	m_vertices =
	{
		// Front vertices
		{
			{-boxSize.x, -boxSize.y, -boxSize.z}, color
		},
		{
			{-boxSize.x, +boxSize.y, -boxSize.z}, color
		},
		{
			{+boxSize.x, +boxSize.y, -boxSize.z}, color
		},
		{
			{+boxSize.x, -boxSize.y, -boxSize.z}, color
		},
		// Back vertices
		{
			{-boxSize.x, -boxSize.y, +boxSize.z}, color
		},
		{
			{-boxSize.x, +boxSize.y, +boxSize.z}, color
		},
		{
			{+boxSize.x, +boxSize.y, +boxSize.z}, color
		},
		{
			{+boxSize.x, -boxSize.y, +boxSize.z}, color
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

	RenderedGameObject::init();
}
