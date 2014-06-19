#pragma once
#include <memory>
#include <Graphics\PrimitiveType.h>

class VertexDeclaration;
class IVertexBuffer
{
public:
	// hmm, maybe this doesn't have to be a function template. instead, take VertexDeclaration as a parameter? and Vertex* -> void* i-dont-fucking-know
	template<typename Vertex>
	static std::unique_ptr<IVertexBuffer> CreateVertexBuffer(const Vertex* vertexData, int vertexCount)
	{
		return IVertexBuffer::CreateVertexBuffer(Vertex::GetVertexDeclaration(), static_cast<const void*>(vertexData), vertexCount, sizeof(Vertex));
	}

	static std::unique_ptr<IVertexBuffer> CreateVertexBuffer();

	template<typename Vertex>
	void SetVertexData(const Vertex* vertexData, int vertexCount)
	{
		this->SetData(Vertex::GetVertexDeclaration(), static_cast<const void*>(vertexData), vertexCount, sizeof(Vertex));
	}

	virtual int GetVertexCount() const = 0;
	virtual void Bind() = 0;
	virtual ~IVertexBuffer() { }

	virtual int GetPrimitiveCount(PrimitiveType primitiveType);

protected:
	virtual void SetData(const VertexDeclaration& vertexDeclaration, const void* vertexData, int vertexCount, int sizeOfVertex) = 0;

private:
	static std::unique_ptr<IVertexBuffer> CreateVertexBuffer(const VertexDeclaration& vertexDeclaration, const void* vertexData, int vertexCount, int sizeOfVertex);
};
