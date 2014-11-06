#pragma once

enum class TextureFormat
{
	None,
	RBGA8,
	RBG8,
	Red8,
};

namespace TextureFormatHelper
{
	static int GetPixelSizeInBytes(const TextureFormat& textureFormat)
	{
		switch (textureFormat)
		{
		case TextureFormat::RBGA8:
			return 4;

		case TextureFormat::RBG8:
			return 3;

		case TextureFormat::Red8:
			return 1;

		case TextureFormat::None:
			return 0;
		}
	}
}