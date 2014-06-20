#pragma once
#include <Graphics\VertexDeclaration.h>
#include <Graphics\OpenGL\OGL.h>
#include <Graphics\OpenGL\OGL-Helper.h>

#include <Graphics\IVertexBuffer.h>

namespace OGL
{
	// blahh.. just make the .cpp file :P
	class VertexBuffer : public IVertexBuffer
	{
	public:
		static std::unique_ptr<IVertexBuffer> CreateVertexBuffer()
		{
			GLuint vertexArrayID;
			glGenVertexArrays(1, &vertexArrayID);
			glBindVertexArray(vertexArrayID);

			GLuint vertexBufferID;
			glGenBuffers(1, &vertexBufferID);
			glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);

			VertexBuffer* vertexBuffer = new VertexBuffer(vertexArrayID, vertexBufferID, 0);
			return std::unique_ptr<VertexBuffer>(vertexBuffer);
		}

		virtual void SetData(const VertexDeclaration& vertexDeclaration, const void* vertexData, int vertexCount, int sizeOfVertex) override
		{
		    glBindVertexArray(_vertexArrayID); // ??? not needed pretty sure. "Bind the VAO to draw. Bind the VBO to modify the VBO." // update: i'll take that back. for some reason, without this, if I have multiple VAO's/vertex buffers and set data one one,
											   // the data will change on the other one too
			glBindBuffer(GL_ARRAY_BUFFER, _vertexBufferID);
			glBufferData(GL_ARRAY_BUFFER, sizeOfVertex * vertexCount, vertexData, GL_STATIC_DRAW);

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
			_hasData = true; // except if vertexCount == 0?
		}

		virtual void Bind() 
		{
			glBindVertexArray(_vertexArrayID);
		}

		virtual int GetVertexCount() const override
		{
			return _vertexCount;
		}

		virtual ~VertexBuffer()
		{
			glDeleteBuffers(1, &_vertexBufferID);
			glDeleteVertexArrays(1, &_vertexArrayID);
		}

	private:
		VertexBuffer(GLuint vertexArrayID, GLuint vertexBufferID, int vertexCount) : _vertexArrayID(vertexArrayID), _vertexBufferID(vertexBufferID), _vertexCount(vertexCount) { }
		GLuint _vertexArrayID;
		GLuint _vertexBufferID;
		int _vertexCount;

		bool _hasData = false;
	};
}