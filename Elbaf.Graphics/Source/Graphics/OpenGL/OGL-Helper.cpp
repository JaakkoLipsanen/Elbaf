#include "OGL-Helper.h"
#include <Graphics\ClearOptions.h>
#include <Graphics\CompareFunction.h>
#include <Graphics\IGraphicsDevice.h>
#include <Graphics\VertexElement.h>
#include <system_error>

GLbitfield OGL::GetClearMask(ClearOptions const& clearOptions)
{
#define BIT(X)  GL_##X##_BUFFER_BIT
	static const GLbitfield MapToGL[] = { BIT(COLOR), BIT(DEPTH), BIT(STENCIL), BIT(COLOR) | BIT(DEPTH) | BIT(STENCIL) };
	return MapToGL[static_cast<int>(clearOptions)];
}

GLenum OGL::CompareFunctionToGLenum(CompareFunction const& compareFunction)
{
	static const GLenum MapToGL[] = { GL_NEVER, GL_ALWAYS, GL_EQUAL, GL_NOTEQUAL, GL_LESS, GL_LEQUAL, GL_GREATER, GL_GEQUAL };
	return MapToGL[static_cast<int>(compareFunction)];
}

GLenum OGL::CullFaceToGLenum(CullFace const& cullFace)
{
	static const GLenum MapToGL[] = { GL_FRONT, GL_BACK, GL_FRONT_AND_BACK };
	return MapToGL[static_cast<int>(cullFace)];
}

GLenum OGL::VertexElementTypeToGLenum(VertexElementType elementType)
{
	switch (elementType)
	{
	case VertexElementType::SByte:
		return GL_BYTE;

	case VertexElementType::Byte:
		return GL_UNSIGNED_BYTE;

	case VertexElementType::Short:
		return GL_SHORT;

	case VertexElementType::UShort:
		return GL_UNSIGNED_SHORT;

	case VertexElementType::Int:
		return GL_INT;

	case VertexElementType::UInt:
		return GL_UNSIGNED_INT;

	case VertexElementType::HalfFloat:
		return GL_HALF_FLOAT;

	case VertexElementType::Float:
		return GL_FLOAT;

	case VertexElementType::Double:
		return GL_DOUBLE;

	default:
		throw std::logic_error("Unknown element type");
	}
}