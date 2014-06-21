#include <Graphics\IVertexBuffer.h>
#include <system_error>

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