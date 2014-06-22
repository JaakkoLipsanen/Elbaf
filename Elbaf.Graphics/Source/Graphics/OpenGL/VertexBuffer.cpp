#include <Graphics\OpenGL\VertexBuffer.h>

#include <Graphics\OpenGL\OGL-Helper.h>
#include <Graphics\VertexDeclaration.h>

std::unique_ptr<IVertexBuffer> OGL::VertexBuffer::CreateVertexBuffer(BufferType bufferType)
{
	GLuint vertexArrayID;
	glGenVertexArrays(1, &vertexArrayID);
	glBindVertexArray(vertexArrayID);

	GLuint vertexBufferID;
	glGenBuffers(1, &vertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);

	VertexBuffer* vertexBuffer = new VertexBuffer(vertexArrayID, vertexBufferID, bufferType);
	return std::unique_ptr<VertexBuffer>(vertexBuffer);
}

void OGL::VertexBuffer::SetData(VertexDeclaration const& vertexDeclaration, void const* vertexData, int vertexCount, int sizeOfVertex)
{
	glBindVertexArray(_vertexArrayID); // ??? not needed pretty sure. "Bind the VAO to draw. Bind the VBO to modify the VBO." // update: i'll take that back. for some reason, without this, if I have multiple VAO's/vertex buffers and set data one one,
	// the data will change on the other one too
	glBindBuffer(GL_ARRAY_BUFFER, _vertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, sizeOfVertex * vertexCount, vertexData, (_bufferType == BufferType::Static) ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW);
	
	for (int i = 0; i < vertexDeclaration.GetCount(); i++)
	{
		auto& element = vertexDeclaration[i];
		glEnableVertexAttribArray(element.AttributeIndex);
		glVertexAttribPointer( //  plaahh, should use glVertexAttribIPointer for integer values... have to do some kind of distinction in VertexElement I guess
			element.AttributeIndex,
			element.ComponentCount,
			VertexElementTypeToGLenum(element.ElementType),
			element.Normalized, // remember, this isn't valid for non-integer types. there could be a check for this?
			sizeOfVertex,
			reinterpret_cast<void*>(element.Offset)); // should offset be calculated automatically? could and should be possible.. although that would require the vertex elements be always in order
	}

	glBindVertexArray(-1);
	_vertexCount = vertexCount;
	_hasData = (_vertexCount == 0); // except if vertexCount == 0?
}

void OGL::VertexBuffer::Bind()
{
	glBindVertexArray(_vertexArrayID);
}

int OGL::VertexBuffer::GetVertexCount() const
{
	return _vertexCount;
}

BufferType OGL::VertexBuffer::GetBufferType() const
{
	return _bufferType;
}

OGL::VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &_vertexBufferID);
	glDeleteVertexArrays(1, &_vertexArrayID);
}