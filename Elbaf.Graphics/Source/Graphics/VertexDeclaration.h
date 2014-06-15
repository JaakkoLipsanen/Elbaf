#pragma once
#include <Graphics\VertexElement.h>
#include <vector>

class VertexDeclaration
{
public:
	VertexDeclaration(std::vector<VertexElement> vertexElements) : _vertexElements(vertexElements), Count(static_cast<int>(vertexElements.size()))
	{
	}

	int GetCount() const
	{
		return this->Count;
	}

	const VertexElement& operator[](int index) const
	{
		return _vertexElements[index];
	}

private:
	const int Count;
	std::vector<VertexElement> _vertexElements;
};