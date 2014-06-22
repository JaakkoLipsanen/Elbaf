#pragma once

enum class PrimitiveType
{
	TriangleList,
	TriangleStrip,
	// TriangleFan, // dont use, not supported in modern D3D and suppousedly slow. should be easy to simulate using TriangleStrip

	LineList,
	LineStrip,
	Points, // not sure if supported by D3D
};