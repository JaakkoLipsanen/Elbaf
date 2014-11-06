#pragma once
#include <Graphics\OpenGL\OGL.h>

enum class ClearOptions;
enum class CompareFunction;
enum class CullFace;
enum class VertexElementType;
enum class PrimitiveType;
enum class TextureFormat;
enum class BlendFactor;
enum class BlendFunction;
enum class DepthBufferFormat;

namespace OGL
{
	GLbitfield GetClearMask(const ClearOptions& clearOptions);
	GLenum CompareFunctionToGLenum(const CompareFunction& compareFunction);
	GLenum CullFaceToGLenum(const CullFace& cullFace);

	GLenum VertexElementTypeToGLenum(VertexElementType elementType);
	GLenum PrimitiveTypeToGLenum(PrimitiveType primitiveType);
	GLenum TextureFormatToGLenum(TextureFormat textureFormat);
	GLenum SamplerIndexToGLenum(unsigned int samplerIndex);

	GLenum BlendFactorToGLenum(BlendFactor blendFactor);
	GLenum BlendFunctionToGLenum(BlendFunction blendFunction);

	GLenum DepthBufferFormatToGLenum(const DepthBufferFormat& depthBufferFormat);
}