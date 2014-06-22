#pragma once
#include <Input\InputModule.h>

#include <GLFW\glfw3.h>
#include <algorithm>
#include <Input\KeyboardState.h>
#include <Input\MouseState.h>
#include <Diagnostics\Logger.h>
#include <Core\Array.h>
#include <Core\IEngine.h>
#include <Core\IGameWindow.h>
#include <Math\Vector.h>

static IInputProvider* CreateInputProvider();
InputModule::InputModule(IEngine& engine) : IModule(engine), _inputProvider(CreateInputProvider())
{
}

void InputModule::Initialize()
{
}

void InputModule::BeginFrame()
{
	_inputProvider->BeginFrame();
}

void InputModule::EndFrame()
{
	_inputProvider->EndFrame();
}

void InputModule::Terminate()
{
	_inputProvider->Terminate();
}

IInputProvider& InputModule::GetInputProvider()
{
	return *(_inputProvider.get());
}

#if OPENGL
#include <Input\GLFW\InputProvider.h>
static IInputProvider* CreateInputProvider()
{
	return new GLFW::InputProvider();
}
#endif