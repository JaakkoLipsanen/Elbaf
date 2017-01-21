## Elbaf, an OpenGL and C++ game engine

Elbaf is a project that I developed around late 2014 and early 2015. It is a game engine that is built from "scratch" with C++ and OpenGL.
The project is splitted in to different projects, that I call **modules**:

**Elbaf.Content** handles loading assets, such as textures and fonts

**Elbaf.Core** is the module that contains all the stuff that doesn't belong into any other module, for example many general helper classes

**Elbaf.Diagnostics** contains all debug stuff, such as logging and assertation

**Elbaf.Engine** is the main module, which handles loading all other modules and runs the game

**Elbaf.Graphics** encapsulates graphics API's (only OpenGL at the moment) and has all graphics related classes (both low level classes like `GraphicsDevice` or `DepthState` and higher level classes like `SpriteBatch` or post processing stuff)

**Elbaf.Input** encapsulates low-level input API's and exposes them in `Input` and `Mouse` classes

**Elbaf.Math** contains all math related classes

Every project has both *public* and *private* headers. Private headers are meant to be used only within that module and are located in the project's `/Source` folder, where as public headers are meant to be used by other modules of the engine and projects using the engine. Public headers are located in the project's `/Include` folder. 

The modules expose their API usually in a class inheriting from `IModule`. For example, Elbaf.Content exposes the functionality in `ContentModule.h`/`Content.h`, Elbaf.Input exposes in `InputModule.h`/`Input.h` and Elbaf.Graphics in `GraphicsModule.h`.

### Current state of the project
Currently, all the main functionality works, such as loading assets, getting input, handling multiple scenes and rendering. 

The `SpriteBatch` class in the Graphics module supports rendering 2D textures and fonts, and is perfectly usable for 2D games. I have developed a simple game Tetris game with Elbaf, [Tetris++](https://github.com/JaakkoLipsanen/Tetris.PlusPlus).

3D support is working as well, with `GraphicsContext` and `VertexBuffer` classes being the main API's for rendering 3D graphics. Custom GLSL shaders are supported as well, as is post processing through `PostProcess` and `PostProcessRenderer` classes. The GLSL support several additional features that were made possible through preprocessing the shader files (in `OGL-ShaderLoader` class), such as `#(include file_name)` which allows you to combine different files into a single shader and `#(fragment-shader)` and `#(vertex-shader)` specifiers which allows you to have both vertex and fragment shaders in the same file.

If I ever decide to continue this project, the main priorities would be to create a Renderer class which handles rendering all the objects and post process effects. This is already under progress in **Elbaf.Testing**. Another thing, would be to create an entity system which manages all game objects in the game. A *component-based entity system* (CBES) is in my experience the way to go.


This was my first large C++ project, so the project might contains some stuff that is not considered "a good practice". However, I learned a lot during this project about C++ and I think the code is pretty good: it is clean, consistent and easy to read. I tried to use modern C++ (C++11/C++14) as much as I could, so I use features like smart pointers, `nullptr`, `auto`, strongly typed enums and range-based for loops as much as I could. One of the programming patterns that I used very extensively in this project was the *pointer-to-implementation* (pimpl) pattern, which hides all the private instance variables and methods from the header files and moves them to an `Impl` struct in the .cpp. An example of this is for example the `SpriteBatch` class. In [SpriteBatch.h], the header file, I only have three includes, where as in the [SpriteBatch.cpp] I have 14 includes. This is thanks to the fact that the only instance variable that is in the header is `class Impl; std::unique_ptr<Impl>* _pImpl;` The `Impl` class, which is defined in the .cpp, stores all of the instance variables that SpriteBatch needs to function. This is a really great pattern in my opinion, although necessary only because of the design of C++.

*Screenshots of the demo scene that I use for developing and testing new features*
![screenshot 1](/Documentation/Screenshot1.png)
![screenshot 2](/Documentation/Screenshot2.png)

[Spritebatch.cpp]: https://github.com/JaakkoLipsanen/Elbaf/blob/master/Elbaf.Graphics/Source/Graphics/SpriteBatch.cpp
[Spritebatch.h]: https://github.com/JaakkoLipsanen/Elbaf/blob/master/Elbaf.Graphics/Include/Graphics/SpriteBatch.h
