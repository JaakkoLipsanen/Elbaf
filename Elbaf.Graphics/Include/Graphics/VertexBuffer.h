#pragma once
#include <memory>
#include <Graphics\PrimitiveType.h>

enum class BufferType
{
	Static,
	Dynamic,
};

class VertexDeclaration;
class VertexBuffer
{
public:
	template<typename Vertex>
	void SetVertexData(const Vertex* vertexData, int vertexCount)
	{
		this->SetData(Vertex::GetVertexDeclaration(), static_cast<const void*>(vertexData), vertexCount, sizeof(Vertex));
	}

	virtual BufferType GetBufferType() const = 0;
	virtual int GetVertexCount() const = 0;
	virtual void Bind() = 0;
	virtual ~VertexBuffer() { }

	virtual int GetPrimitiveCount(PrimitiveType primitiveType);

protected:
	virtual void SetData(const VertexDeclaration& vertexDeclaration, const void* vertexData, int vertexCount, int sizeOfVertex) = 0;
};
