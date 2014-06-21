#include <Input\Mouse.h>
#include <GLFW\glfw3.h>
#include <Core\Engine.h>
#include <Core\IGameWindow.h>

#if !OPENGL
#error("Not implemented")
#endif

static GLFWwindow* GetWindow()
{
	return static_cast<GLFWwindow*>(IEngine::GetInstance().GetWindow().GetInternalHandle());
}

void Mouse::SetCursorVisibility(CursorVisibility cursorType)
{
	auto value = (cursorType == CursorVisibility::Visible ? GLFW_CURSOR_NORMAL : (cursorType == CursorVisibility::Hidden ? GLFW_CURSOR_HIDDEN : GLFW_CURSOR_DISABLED));
	glfwSetInputMode(GetWindow(), GLFW_CURSOR, value);
}

void Mouse::SetPosition(const Vector2f& position)
{
	glfwSetCursorPos(GetWindow(), position.x, position.y);
}