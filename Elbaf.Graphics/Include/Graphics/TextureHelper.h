#pragma once
#include <memory>
#include <Graphics/ITexture.h>
#include <Graphics/IGraphicsContext.h>
#include <Graphics/Image.h>
#include <Core/Color.h>
#include <Graphics/TextureFormat.h>

namespace TextureHelper
{
	std::unique_ptr<ITexture2D> CreateBlankTexture(IGraphicsContext& graphicsContext)
	{
		static const Color ImageSource[1] = { Color::White };
		static const ::Image Image(&ImageSource, 1, 1, TextureFormat::RBGA8, false);

		return graphicsContext.CreateTexture2D(Image);
	}
}