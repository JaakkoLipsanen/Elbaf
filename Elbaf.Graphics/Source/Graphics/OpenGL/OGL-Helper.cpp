#include "OGL-Helper.h"
#include <Graphics\ClearOptions.h>
#include <Graphics\CompareFunction.h>
#include <Graphics\IGraphicsDevice.h>

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