#include "VertexFormats.h"
#include <Graphics\VertexElement.h>
#include <Graphics\VertexDeclaration.h>

// VertexPosition
const VertexDeclaration VertexPosition::Declaration = VertexDeclaration({ 
	VertexElement(0, 3, VertexElementType::Float, false, offsetof(VertexPosition, Position)) });

// VertexPositionColor
const VertexDeclaration VertexPositionColor::Declaration = VertexDeclaration({
	VertexElement(0, 3, VertexElementType::Float, false, offsetof(VertexPositionColor, Position)),
	VertexElement(1, 3, VertexElementType::Float, false, offsetof(VertexPositionColor, Color)) });
