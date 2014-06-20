#include "VertexFormats.h"
#include <Graphics\VertexElement.h>
#include <Graphics\VertexDeclaration.h>

// VertexPosition
const VertexDeclaration VertexPosition::Declaration = VertexDeclaration({ 
	VertexElement(0, 3, VertexElementType::Float, false, offsetof(VertexPosition, Position)) });

// VertexPositionColor
const VertexDeclaration VertexPositionColor::Declaration = VertexDeclaration({
	VertexElement(0, 3, VertexElementType::Float, false, offsetof(VertexPositionColor, Position)),
	VertexElement(1, 4, VertexElementType::Float, false, offsetof(VertexPositionColor, Color)) });

// VertexPositionColorTexture
const VertexDeclaration VertexPositionColorTexture::Declaration = VertexDeclaration({
	VertexElement(0, 3, VertexElementType::Float, false, offsetof(VertexPositionColorTexture, Position)),
	VertexElement(1, 4, VertexElementType::Float, false, offsetof(VertexPositionColorTexture, Color)),
	VertexElement(2, 2, VertexElementType::Float, false, offsetof(VertexPositionColorTexture, TextureCoordinate)) });
