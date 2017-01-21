## Elbaf, an OpenGL and C++ game engine

Elbaf is a project that I developed around late 2014 and early 2015. It is a game engine that is built from 'scratch' with C++ and OpenGL.
The project is splitted in to different projects, that I call **modules**:

**Elbaf.Content** handles loading assets, such as textures and fonts

**Elbaf.Core** is the module that contains all the stuff that doesn't belong into any other module, for example many general helper classes

**Elbaf.Diagnostics** contains all debug stuff, such as logging and assertation

**Elbaf.Engine** is the main module, which handles loading all other modules and runs the game

**Elbaf.Graphics** encapsulates graphics API's (only OpenGL at the moment) and has all graphics related classes (both low level classes like *GraphicsDevice* or *DepthState* and higher level like *SpriteBatch* or post processing stuff)

**Elbaf.Input** encapsulates low-level input API's and exposes them in Input and Mouse classes

**Elbaf.Math** contains all math related classes

Every project has both *public* and *private* headers. Private headers are meant to be used only within that module and are located in the */Source* folder, where as public headers are meant to be used by other modules of the engine and games developed using the engine. Public headers are located in the */Include* folder. 

The modules expose their API usually in a class inheriting from *IModule*. For example, Elbaf.Content exposes the functionality in *ContentModule.h*/*Content.h*, Elbaf.Input exposes in *InputModule.h*/*Input.h*, Elbaf.Graphics in *GraphicsModule.h* etc.

### Current state of the project
The current state of the engine is that all main functionality works, such as loading assets, getting input, handling multiple scenes and rendering. 

The *SpriteBatch* class in the Graphics module supports rendering 2D textures and fonts, and is perfectly usable for 2D games. I have developed a simple game Tetris game with Elbaf, [Tetris++](https://github.com/JaakkoLipsanen/Tetris.PlusPlus).

3D support is working as well, with *GraphicsContext* and *VertexBuffer* classes being the main API's for rendering 3D graphics. Custom GLSL shaders are supported as well, as is post processing through *PostProcess* and *PostProcessRenderer* classes. The GLSL support several additional features that were made possible through preprocessing the shader files (in *OGL-ShaderLoader* class), such as *#(include file_name)* which allows you to combine different files into a single shader and *#(fragment-shader)* and *#(vertex-shader)* specifiers which allows you to have both vertex and fragment shaders in the same file.

If I ever decide to continue this project, the main priorities would be to create a Renderer class which handles rendering all the objects and post process effects. This is already under progress in **Elbaf.Testing**. Another thing, would be to create an entity system which manages all game objects in the game. A *component-based entity system* (CBES) is in my experience the way to go.

*Screenshots of the demo scene that I use for developing and testing new features*
![screenshot 1](/Documentation/Screenshot1.png)
![screenshot 2](/Documentation/Screenshot2.png)
