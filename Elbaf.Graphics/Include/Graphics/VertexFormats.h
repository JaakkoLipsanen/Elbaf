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
	Vector4f Color; // todo: just use Color and send the data to gpu as 3x Byte (normalized)? also, this should be 4-element (alpha)....
	/* -|- !!!! */
	VertexPositionColor(Vector3f position, ::Color color) : Position(position), Color(color.ToVector4f())
	{
	}

	static const VertexDeclaration Declaration; // = VertexDeclaration({ VertexElement(), VertexElement() }); // VertexDeclaration({ VertexElement() });
	static const VertexDeclaration& GetVertexDeclaration()
	{
		return Declaration;
	}
};

// okay... right now this takes 32-bits. But if I make the color into Vector4f, then it will take 36bits :(  I think that might mess things ups
struct VertexPositionColorTexture
{	
	Vector3f Position;
	Vector4f Color; // todo: just use Color and send the data to gpu as 3x Byte (normalized)? also, this should be 4-element (alpha)....
	Vector2f TextureCoordinate;
	/* -|- !!!! */
	VertexPositionColorTexture(Vector3f position, ::Color color, Vector2f textureCoordinate) : Position(position), Color(color.ToVector4f()), TextureCoordinate(textureCoordinate)
	{
	}

	static const VertexDeclaration Declaration; // = VertexDeclaration({ VertexElement(), VertexElement() }); // VertexDeclaration({ VertexElement() });
	static const VertexDeclaration& GetVertexDeclaration()
	{
		return Declaration;
	}
};