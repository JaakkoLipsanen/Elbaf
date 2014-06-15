#pragma once
#include <memory>

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

	virtual void Bind() = 0;
	virtual ~IVertexBuffer() { } 

private:
	static std::unique_ptr<IVertexBuffer> CreateVertexBuffer(const VertexDeclaration& vertexDeclaration, const void* vertexData, int vertexCount, int sizeOfVertex);
};
