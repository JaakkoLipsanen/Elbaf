#pragma once

// to it's own file?
enum class VertexElementType
{
	SByte,
	Byte,
	Short,
	UShort,
	Int,
	UInt,

	HalfFloat,
	Float,
	Double
};

struct VertexElement final
{
	int AttributeIndex;
	int ComponentCount;
	VertexElementType ElementType;
	bool Normalized;
	int Offset; // this isnt necessarily needed, since it should be possible to calculate this automatically.. todo? though with offsetof this isnt much work

	VertexElement(int attributeIndex, int componentCount, VertexElementType elementType, bool isNormalized, int offset) :
		AttributeIndex(attributeIndex), ComponentCount(componentCount), ElementType(elementType), Normalized(isNormalized), Offset(offset)
	{
	}
};