#include <Graphics\VertexFormats.h>
#include <Graphics\VertexElement.h>
#include <Graphics\VertexDeclaration.h>

// VertexPosition
const VertexDeclaration VertexPosition::Declaration = VertexDeclaration({ 
	VertexElement(0, 3, VertexElementType::Float, false, offsetof(VertexPosition, Position)) });

// VertexPositionColor
const VertexDeclaration VertexPositionColor::Declaration = VertexDeclaration({
	VertexElement(0, 3, VertexElementType::Float, false, offsetof(VertexPositionColor, Position)),
	VertexElement(1, 4, VertexElementType::Float, false, offsetof(VertexPositionColor, Color)) });


// VertexPositionTexture
const VertexDeclaration VertexPositionTexture::Declaration = VertexDeclaration({
	VertexElement(0, 3, VertexElementType::Float, false, offsetof(VertexPositionTexture, Position)),
	// Color
	VertexElement(2, 2, VertexElementType::Float, false, offsetof(VertexPositionTexture, TextureCoordinate)) });

// VertexPositionColorTexture
const VertexDeclaration VertexPositionColorTexture::Declaration = VertexDeclaration({
	VertexElement(0, 3, VertexElementType::Float, false, offsetof(VertexPositionColorTexture, Position)),
	VertexElement(1, 4, VertexElementType::Float, false, offsetof(VertexPositionColorTexture, Color)),
	VertexElement(2, 2, VertexElementType::Float, false, offsetof(VertexPositionColorTexture, TextureCoordinate)) });

// VertexPositionColorNormal
const VertexDeclaration VertexPositionColorNormal::Declaration = VertexDeclaration({
	VertexElement(0, 3, VertexElementType::Float, false, offsetof(VertexPositionColorNormal, Position)),
	VertexElement(1, 4, VertexElementType::Float, false, offsetof(VertexPositionColorNormal, Color)),
	// UV
	VertexElement(3, 3, VertexElementType::Float, false, offsetof(VertexPositionColorNormal, Normal)) });


// VertexPositionColorTextureNormal
const VertexDeclaration VertexPositionColorTextureNormal::Declaration = VertexDeclaration({
	VertexElement(0, 3, VertexElementType::Float, false, offsetof(VertexPositionColorTextureNormal, Position)),
	VertexElement(1, 4, VertexElementType::Float, false, offsetof(VertexPositionColorTextureNormal, Color)),
	VertexElement(2, 2, VertexElementType::Float, false, offsetof(VertexPositionColorTextureNormal, TextureCoordinate)),
	VertexElement(3, 3, VertexElementType::Float, false, offsetof(VertexPositionColorTextureNormal, Normal)) });



// 0 == position,
// 1 == 