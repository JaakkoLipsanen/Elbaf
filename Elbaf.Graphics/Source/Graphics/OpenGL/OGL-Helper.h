#pragma once
#include "OGL.h"

enum class ClearOptions;
enum class CompareFunction;
enum class CullFace;
enum class VertexElementType;
enum class PrimitiveType;

namespace OGL
{
	GLbitfield GetClearMask(const ClearOptions& clearOptions);
	GLenum CompareFunctionToGLenum(const CompareFunction& compareFunction);
	GLenum CullFaceToGLenum(const CullFace& cullFace);

	GLenum VertexElementTypeToGLenum(VertexElementType elementType);
	GLenum PrimitiveTypeToGLenum(PrimitiveType primitiveType);
}