#pragma once
#include <Math\Vector.h>
#include <Core\Color.h>

class VertexDeclaration;
struct VertexPosition
{
	Vector3f Position;
	VertexPosition(Vector3f position) : Position(position)
	{
	}

	static const VertexDeclaration Declaration; // = VertexDeclaration({ VertexElement(), VertexElement() }); // VertexDeclaration({ VertexElement() });
	static const VertexDeclaration& GetVertexDeclaration()
	{
		return Declaration;
	}
};

struct VertexPositionColor
{
	Vector3f Position;
	Vector3f Color; // todo: just use Color and send the data to gpu as 3x Byte (normalized)? also, this should be 4-element (alpha)....
	/* -|- !!!! */
	VertexPositionColor(Vector3f position, ::Color color) : Position(position), Color(color.ToVector3f())
	{
	}

	static const VertexDeclaration Declaration; // = VertexDeclaration({ VertexElement(), VertexElement() }); // VertexDeclaration({ VertexElement() });
	static const VertexDeclaration& GetVertexDeclaration()
	{
		return Declaration;
	}
};