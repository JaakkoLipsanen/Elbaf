#include "IVertexBuffer.h"
#if OPENGL
#include <Graphics\OpenGL\VertexBuffer.h>
#endif

int IVertexBuffer::GetPrimitiveCount(PrimitiveType primitiveType)
{
	int vertexCount = this->GetVertexCount();
	switch (this->GetVertexCount())
	{
	case PrimitiveType::TriangleList:
		return vertexCount / 3;

	case PrimitiveType::TriangleStrip:
		return vertexCount - 2;

	case PrimitiveType::LineList:
		return vertexCount / 2;

	case PrimitiveType::LineStrip:
		return vertexCount - 1;

	case PrimitiveType::Points:
		return vertexCount;

	default:
		throw std::logic_error("Not implemented");
	}
}

std::unique_ptr<IVertexBuffer> IVertexBuffer::CreateVertexBuffer(VertexDeclaration const& vertexDeclaration, void const* vertexData, int vertexCount, int sizeOfVertex)
{
#if OPENGL
	return OGL::VertexBuffer::CreateVertexBuffer(vertexDeclaration, vertexData, vertexCount, sizeOfVertex);
#else
#error("Not implemented");
#endif
}