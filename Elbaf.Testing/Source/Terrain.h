#pragma once
#include <Core/Global.h>
#include "Renderer.h"
#include <Core/Color.h>
#include <Graphics/VertexFormats.h>
#include <Graphics/IVertexBuffer.h>
#include "NoiseGen.h"
#include <Engine/Stopwatch.h>

class Terrain
{
public:

	Terrain(IGraphicsContext& graphicsContext) :
		_graphicsContext(graphicsContext)
	{
	}

	std::shared_ptr<Mesh> Mesh;
	void Generate()
	{
		const int Size = 256;
		float grid[(Size + 1) * (Size + 1)];
		const float MaxHeight = 1;
		Stopwatch sw("Noise gen");
		for (int y = 0; y < Size + 1; y++)
		{
			for (int x = 0; x < Size + 1; x++)
			{
				grid[x + y * Size] = scaled_octave_noise_2d(24, 0.4f, 0.0015f, 0, 700, x * 4, y * 4) + Global::Random.NextFloat(-0.5f, 0.5f) * 2;
			}
		}
		sw.Stop();

		std::vector<VertexPositionColorNormal> terrainVertexData;
		for (int y = 0; y < Size; y++)
		{
			for (int x = 0; x < Size; x++)
			{
				static const Color From = Color::Lerp(Color::DodgerBlue, Color::White, 1.f); // Color(40, 40, 40);
				static const Color To = From;

				Vector3f blPos = { x, grid[x + y * Size], y };
				Vector3f brPos = { x + 1, grid[x + 1 + y * Size], y };
				Vector3f tlPos = { x, grid[x + (y + 1) * Size], y + 1.0f };
				Vector3f trPos = { x + 1, grid[x + 1 + (y + 1) * Size], y + 1 };

				Vector3f normalFirst = Vector::Cross(tlPos - blPos, brPos - blPos);
				Vector3f normalSecond = -Vector::Cross(tlPos - trPos, brPos - trPos);

				Color blColor = Color::Lerp(From, To, grid[x + y * Size] / MaxHeight);
				Color brColor = Color::Lerp(From, To, grid[x + 1 + y * Size] / MaxHeight);
				Color tlColor = Color::Lerp(From, To, grid[x + (y + 1) * Size] / MaxHeight);
				Color trColor = Color::Lerp(From, To, grid[x + 1 + (y + 1) * Size] / MaxHeight);

				typedef VertexPositionColorNormal V;

				terrainVertexData.emplace_back(blPos, blColor, normalFirst);
				terrainVertexData.push_back(V(tlPos, tlColor, normalFirst));
				terrainVertexData.push_back(V(brPos, brColor, normalFirst));

				terrainVertexData.push_back(V(tlPos, tlColor, normalSecond));
				terrainVertexData.push_back(V(trPos, trColor, normalSecond));
				terrainVertexData.push_back(V(brPos, brColor, normalSecond));
			}
		}
		

	    std::shared_ptr<IVertexBuffer> x(_graphicsContext.CreateVertexBuffer(BufferType::Static).release());
		this->Mesh.reset(new ::Mesh(x));
		Stopwatch sw2("Mesh gen");
		this->Mesh->VertexBuffer->SetVertexData(terrainVertexData.data(), terrainVertexData.size());
		sw2.Stop();

		Logger::LogMessage(terrainVertexData.size());
	}

private:
	IGraphicsContext& _graphicsContext;
};