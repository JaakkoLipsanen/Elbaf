#include <Graphics\Image.h>
#include <cstdlib>

Image::~Image()
{
	// meh. casting const pointer to non-const pointer. but whatever..
	// also I'm really not sure if it's a good idea for this to automatically delete the image data, after all the 'user' might want to keep it in memory?
	free((void*)this->ImageData);
}