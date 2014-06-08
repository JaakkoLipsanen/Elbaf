#pragma once

#if !OPENGL
 #error ("Error: This is an OpenGL-specific class and "OPENGL" preprocessor is not defined!")
#endif

// TODO: Put this header in the "private" headers section! No other module should be allowed to access GL/API specific stuff or functions!

// yeah... dont know if this is a good idea :P
#ifndef GLEW_STATIC
#define GLEW_STATIC
#endif

#include <GL\glew.h>
#include <GLFW\glfw3.h>