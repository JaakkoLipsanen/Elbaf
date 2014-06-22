#pragma once
#include <Graphics\OpenGL\OGL.h>
#include <Graphics\IVertexBuffer.h>

namespace OGL
{
	class VertexBuffer : public IVertexBuffer
	{
	public:
		static std::unique_ptr<IVertexBuffer> CreateVertexBuffer(BufferType bufferType);

		virtual void SetData(const VertexDeclaration& vertexDeclaration, const void* vertexData, int vertexCount, int sizeOfVertex) override;
		virtual void Bind();
		virtual int GetVertexCount() const override;
		virtual BufferType GetBufferType() const override;

		virtual ~VertexBuffer();

	private: // pimpl?
		VertexBuffer(GLuint vertexArrayID, GLuint vertexBufferID, BufferType bufferType, int vertexCount = 0) : _vertexArrayID(vertexArrayID), _vertexBufferID(vertexBufferID), _bufferType(bufferType), _vertexCount(vertexCount) { }
		GLuint _vertexArrayID;
		GLuint _vertexBufferID;

		BufferType _bufferType;
		int _vertexCount;
		bool _hasData = false;
	};
}