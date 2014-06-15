#pragma once
#include <Graphics\VertexDeclaration.h>
#include <Graphics\OpenGL\OGL.h>
#include <Graphics\OpenGL\OGL-Helper.h>

#include <Graphics\IVertexBuffer.h>

namespace OGL
{
	class VertexBuffer : public IVertexBuffer
	{
	public:
		static std::unique_ptr<IVertexBuffer> CreateVertexBuffer(const VertexDeclaration& vertexDeclaration, const void * vertexData, int vertexCount, int sizeOfVertex)
		{
			GLuint vertexArrayID;
			glGenVertexArrays(1, &vertexArrayID);
			glBindVertexArray(vertexArrayID);

			GLuint vertexBufferID;
			glGenBuffers(1, &vertexBufferID);
			glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
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

			glBindVertexArray(0);
			return std::unique_ptr<IVertexBuffer>(new VertexBuffer(vertexArrayID, vertexBufferID));
		}

		virtual void Bind() 
		{
			glBindVertexArray(_vertexArrayID);
		}

		virtual ~VertexBuffer()
		{
			glDeleteBuffers(1, &_vertexBufferID);
			glDeleteVertexArrays(1, &_vertexArrayID);
		}

	private:
		VertexBuffer(GLuint vertexArrayID, GLuint vertexBufferID) : _vertexArrayID(vertexArrayID), _vertexBufferID(vertexBufferID) { }
		GLuint _vertexArrayID;
		GLuint _vertexBufferID;
	};
}