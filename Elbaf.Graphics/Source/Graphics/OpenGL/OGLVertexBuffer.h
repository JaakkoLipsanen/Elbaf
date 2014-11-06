#pragma once
#include <Graphics\OpenGL\OGL.h>
#include <Graphics\VertexBuffer.h>

namespace OGL
{
	class OGLVertexBuffer : public VertexBuffer
	{
	public:
		static std::unique_ptr<OGL::OGLVertexBuffer> Create(BufferType bufferType);

		virtual void Bind() override;
		virtual int GetVertexCount() const override;
		virtual BufferType GetBufferType() const override;

		virtual ~OGLVertexBuffer();

	protected:
		virtual void SetData(const VertexDeclaration& vertexDeclaration, const void* vertexData, int vertexCount, int sizeOfVertex) override;

	private: // pimpl?
		OGLVertexBuffer(GLuint vertexArrayID, GLuint vertexBufferID, BufferType bufferType, int vertexCount = 0) : _vertexArrayID(vertexArrayID), _vertexBufferID(vertexBufferID), _bufferType(bufferType), _vertexCount(vertexCount) { }
		GLuint _vertexArrayID;
		GLuint _vertexBufferID;

		BufferType _bufferType;
		int _vertexCount;
		bool _hasData = false;
	};
}