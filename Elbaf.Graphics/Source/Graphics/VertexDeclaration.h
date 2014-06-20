#pragma once
#include <Graphics\VertexElement.h>
#include <vector>

class VertexDeclaration
{
public:
	VertexDeclaration(std::vector<VertexElement> vertexElements) : _vertexElements(vertexElements), _count(static_cast<int>(vertexElements.size()))
	{
	}

	int GetCount() const
	{
		return this->_count;
	}

	const VertexElement& operator[](int index) const
	{
		return _vertexElements[index];
	}

private:
	int _count;
	std::vector<VertexElement> _vertexElements;
};