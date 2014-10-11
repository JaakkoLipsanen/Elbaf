#pragma once
#include "png.h"
#include <string>
#include <Graphics\TextureFormat.h>
#include <Diagnostics\Logger.h>

namespace Content
{
	// original: http://stackoverflow.com/a/11297197
	// small modifications: https://github.com/DavidEGrayson/ahrs-visualizer/blob/master/png_texture.cpp
	// I also rewrote this to be clearer
	static bool ReadPNG(const std::string& filePath, int* width, int* height, TextureFormat* textureFormat, void** data)
	{
		typedef png_byte PngByte;
		static const char* FileModeSpecifier = "rb"; // 'r' == read, 'b' == binary
		const char* FileName = filePath.c_str();

		FILE* fileHandle;
		fopen_s(&fileHandle, FileName, "rb");
		if (fileHandle == 0)
		{
			Logger::LogError("ReadPNG: Could not open file " + filePath);
			return false;
		}

		// read the header
		static const int HeaderSize = 8;
		png_byte header[HeaderSize];
		fread(header, sizeof(png_byte), HeaderSize, fileHandle);
		if (png_sig_cmp(header, 0, HeaderSize))
		{
			Logger::LogError("ReadPNG: File (" + filePath + ") is not a PNG!");
			fclose(fileHandle);
			return false;
		}

		png_structp pngPtr = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
		if (!pngPtr)
		{
			Logger::LogError("ReadPNG: png_create_read_struct returned null (" + filePath + ")");
			fclose(fileHandle);
			return false;
		}

		// create png info struct
		png_infop infoPtr = png_create_info_struct(pngPtr);
		if (!infoPtr)
		{
			Logger::LogError("ReadPNG: png_create_info_struct returned null (" + filePath + ")");
			png_destroy_read_struct(&pngPtr, nullptr, nullptr);
			fclose(fileHandle);
			return false;
		}

		// create png info struct
		png_infop end_info = png_create_info_struct(pngPtr);
		if (!end_info)
		{
			Logger::LogError("ReadPNG: png_create_info_struct (end) returned null (" + filePath + ")");
			png_destroy_read_struct(&pngPtr, &infoPtr, nullptr);
			fclose(fileHandle);
			return false;
		}

		// the code in this if statement gets called if libpng encounters an error
#pragma warning(push)
#pragma warning(disable : 4611)
		if (setjmp(png_jmpbuf(pngPtr))) {
			Logger::LogError("ReadPNG: Error from LibPNG (" + filePath + ")");
			png_destroy_read_struct(&pngPtr, &infoPtr, &end_info);
			fclose(fileHandle);
			return false;
		}
#pragma warning(pop)

		// init png reading
		png_init_io(pngPtr, fileHandle);

		// let libpng know you already read the first 8 bytes
		png_set_sig_bytes(pngPtr, HeaderSize); // pretty sure that HeaderSize is 'correct' (it's correct value, but also correct 'semantically'(?)) 

		// read all the info up to the image data
		png_read_info(pngPtr, infoPtr);

		// variables to pass to get info
		int bitDepth, colorType;
		png_uint_32 tempWidth, tempHeight;

		// get info about png
		png_get_IHDR(pngPtr, infoPtr, &tempWidth, &tempHeight, &bitDepth, &colorType, nullptr, nullptr, nullptr);

		if (width) { *width = tempWidth; }
		if (height) { *height = tempHeight; }

		if (bitDepth != 8)
		{
			Logger::LogError("ReadPNG: Invalid bit depth (" + filePath + ")");
			fclose(fileHandle); // umm.. this wasn't in the source but I can't understand why it shouldn't be here?
			return false;
		}

		switch (colorType)
		{
		case PNG_COLOR_TYPE_RGB:
			*textureFormat = TextureFormat::RBG8;
			break;

		case PNG_COLOR_TYPE_RGB_ALPHA:
			*textureFormat = TextureFormat::RBGA8;
			break;

		case PNG_COLOR_TYPE_GRAY:
			if (bitDepth == 8)
			{
				*textureFormat = TextureFormat::Red8;
			}

		default:
			Logger::LogError("ReadPNG: Invalid color type/format (" + filePath + ")");
			fclose(fileHandle); // umm.. this wasn't in the source but I can't understand why it shouldn't be here?
			return false;
		}

		// Update the png info struct.
		png_read_update_info(pngPtr, infoPtr);

		// Row size in bytes.
		png_size_t rowbytes = png_get_rowbytes(pngPtr, infoPtr);

		// align by 4-byte (glTexImage2d requires rows to be 4-byte aligned)
		rowbytes += 3 - ((rowbytes - 1) % 4);

		// Allocate the image_data as a big block, to be given to opengl
		png_byte* imageData = static_cast<png_byte *>(malloc(rowbytes * tempHeight * sizeof(png_byte) + 15));
		if (imageData == NULL)
		{
			Logger::LogError("ReadPNG: Could not allocate memory from PNG image data (" + filePath + ")");
			png_destroy_read_struct(&pngPtr, &infoPtr, &end_info);
			fclose(fileHandle);
			return 0;
		}

		// row_pointers is for pointing to image_data for reading the png with libpng
		png_byte** rowPointers = static_cast<png_byte**>(malloc(tempHeight * sizeof(png_byte*)));
		if (rowPointers == NULL)
		{
			Logger::LogError("ReadPNG: Could not allocate memory from PNG row pointers (" + filePath + ")");
			png_destroy_read_struct(&pngPtr, &infoPtr, &end_info);
			free(imageData);
			fclose(fileHandle);
			return 0;
		}

		// set the individual row_pointers to point at the correct offsets of image_data
		for (unsigned int i = 0; i < tempHeight; i++)
		{
			rowPointers[tempHeight - 1 - i] = imageData + i * rowbytes;
		}

		// read the png into image_data through row_pointers
		png_read_image(pngPtr, rowPointers);
		png_destroy_read_struct(&pngPtr, &infoPtr, &end_info);
		free(rowPointers);
		fclose(fileHandle);

		*data = static_cast<void*>(imageData); // this isn't free'd here, it's up to the caller to free this
		return true;
	}
}