#include "IVertexBuffer.h"
#if OPENGL
#include <Graphics\OpenGL\VertexBuffer.h>
#endif

std::unique_ptr<IVertexBuffer> IVertexBuffer::CreateVertexBuffer(VertexDeclaration const& vertexDeclaration, void const* vertexData, int vertexCount, int sizeOfVertex)
{
#if OPENGL
	return OGL::VertexBuffer::CreateVertexBuffer(vertexDeclaration, vertexData, vertexCount, sizeOfVertex);
#else
#error("Not implemented");
#endif
}