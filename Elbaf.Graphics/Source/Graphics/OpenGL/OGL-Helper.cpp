#include "OGL-Helper.h"
#include <Graphics\ClearOptions.h>
#include <Graphics\CompareFunction.h>
#include <Graphics\IGraphicsDevice.h>
#include <Graphics\VertexElement.h>
#include <Graphics\PrimitiveType.h>
#include <Graphics\TextureFormat.h>
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

GLenum OGL::PrimitiveTypeToGLenum(PrimitiveType primitiveType)
{
	switch (primitiveType)
	{
	case PrimitiveType::TriangleList:
		return GL_TRIANGLES;

	case PrimitiveType::TriangleStrip:
		return GL_TRIANGLE_STRIP;

	case PrimitiveType::LineList:
		return GL_LINES;

	case PrimitiveType::LineStrip:
		return GL_LINE_STRIP;

	case PrimitiveType::Points:
		return GL_POINTS;

	default:
		throw std::logic_error("Unknown primitive type");
	}
}

GLenum OGL::SamplerIndexToGLenum(unsigned samplerIndex)
{
	
	if (samplerIndex > 30)
	{
		throw std::logic_error("Too big value. OpenGL (I think!) supports only 30 samplers");
	}

	// the values are contigious. SAMPLER(1) == SAMPLER(0) + 1, SAMPLER(15) == SAMPLER(0) + 15 etc
#define SAMPLER(i) GL_TEXTURE##i
	return SAMPLER(0) + samplerIndex;
}

GLenum OGL::TextureFormatToGLenum(TextureFormat textureFormat)
{
	switch (textureFormat)
	{
	case TextureFormat::RBGA:
		return GL_RGBA;

	case TextureFormat::RBG:
		return GL_RGB;

	default:
		throw std::logic_error("Unknown texture format");
	}
}