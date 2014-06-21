#pragma once
#include "OGL.h"

enum class ClearOptions;
enum class CompareFunction;
enum class CullFace;
enum class VertexElementType;
enum class PrimitiveType;
enum class TextureFormat;

namespace OGL
{
	GLbitfield GetClearMask(const ClearOptions& clearOptions);
	GLenum CompareFunctionToGLenum(const CompareFunction& compareFunction);
	GLenum CullFaceToGLenum(const CullFace& cullFace);

	GLenum VertexElementTypeToGLenum(VertexElementType elementType);
	GLenum PrimitiveTypeToGLenum(PrimitiveType primitiveType);
	GLenum TextureFormatToGLenum(TextureFormat textureFormat);
	GLenum SamplerIndexToGLenum(unsigned int samplerIndex);
}