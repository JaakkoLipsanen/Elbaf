#pragma once
#include <memory>
#include <string>
#include <Graphics\Image.h>

namespace Content
{
	std::unique_ptr<Image> LoadImage(const std::string& filePath);
}