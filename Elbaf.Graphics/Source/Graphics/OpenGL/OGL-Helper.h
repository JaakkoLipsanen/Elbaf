#pragma once
#include "OGL.h"

enum class ClearOptions;
enum class CompareFunction;
enum class CullFace;
namespace OGL
{
	GLbitfield GetClearMask(const ClearOptions& clearOptions);
	GLenum CompareFunctionToGLenum(const CompareFunction& compareFunction);
	GLenum CullFaceToGLenum(const CullFace& cullFace);
}