#include <Input\GLFW\InputProvider.h>

#include <system_error>
#include <algorithm>
#include <GLFW\glfw3.h>

#include <Diagnostics\Logger.h>
#include <Core\Array.h>
#include <Input\KeyCode.h>
#include <Input\KeyboardState.h>
#include <Input\MouseState.h>
#include <Core\IEngine.h>
#include <Core\IGameWindow.h>

static int KeyCodeToGLFWKey(KeyCode keyCode);
static void OnScrollWheelCallback(GLFWwindow* window, double xOffset, double yOffset);
static int GetScrollWheelValue();
class GLFW::InputProvider::Impl
{
public:
	GLFWwindow* GlfwWindow;

	// TODO: These doesn't have to be pointers necessary. look into std::swap
	std::unique_ptr<KeyboardState> CurrentKeyboardState;
	std::unique_ptr<KeyboardState> PreviousKeyboardState;

	std::unique_ptr<MouseState> CurrentMouseState;
	std::unique_ptr<MouseState> PreviousMouseState;

	Impl() : 
		CurrentKeyboardState(new KeyboardState), PreviousKeyboardState(new KeyboardState), CurrentMouseState(new MouseState), PreviousMouseState(new MouseState)
	{
		this->ResetStates();

		this->GlfwWindow = static_cast<GLFWwindow*>(IEngine::GetInstance().GetWindow().GetInternalHandle());
		glfwSetScrollCallback(this->GlfwWindow, OnScrollWheelCallback);

		// enable sticky keys. sticky keys means, that key press will be registered even if key has been pressed & released between frames. todo: make this into options?
		glfwSetInputMode(this->GlfwWindow, GLFW_STICKY_KEYS, GL_TRUE);
		glfwSetInputMode(this->GlfwWindow, GLFW_STICKY_MOUSE_BUTTONS, GL_TRUE); // same for mouse buttons
	}

	void GLFWScrollWheelCallback(GLFWwindow* window, double xOffset, double yOffset)
	{
		this->CurrentMouseState->ScrollWheelDelta = static_cast<int>(yOffset);
	}

	void UpdateState()
	{
		std::swap(this->PreviousMouseState, this->CurrentMouseState);

		double x, y;
		glfwGetCursorPos(this->GlfwWindow, &x, &y);
		this->CurrentMouseState->MousePosition = Vector2f(x, y);
		this->CurrentMouseState->ScrollWheelDelta = GetScrollWheelValue();
		for (int i = 0; i < MouseState::ButtonCount; i++)
		{
			this->CurrentMouseState->SetValue(i, glfwGetMouseButton(this->GlfwWindow, i) == GLFW_PRESS);
		}

		std::swap(this->PreviousKeyboardState, this->CurrentKeyboardState);
		for (int i = 0; i < KeyboardState::KeyCount; i++)
		{
			this->CurrentKeyboardState->SetValue(i, glfwGetKey(this->GlfwWindow, KeyCodeToGLFWKey(static_cast<KeyCode>(i))) == GLFW_PRESS);
		}
	}

private:
	void ResetStates()
	{
		for (int i = 0; i < KeyboardState::KeyCount; i++)
		{
			this->PreviousKeyboardState->SetValue(i, false);
			this->CurrentKeyboardState->SetValue(i, false);
		}

		for (int i = 0; i < MouseState::ButtonCount; i++)
		{
			this->CurrentMouseState->SetValue(i, false);
			this->PreviousMouseState->SetValue(i, false);
		}

		this->CurrentMouseState->ScrollWheelDelta = 0;
		this->CurrentMouseState->MousePosition = Vector2f(0, 0);

		this->PreviousMouseState->ScrollWheelDelta = 0;
		this->PreviousMouseState->MousePosition = Vector2f(0, 0);
	}
};

GLFW::InputProvider::InputProvider() : _pImpl(new Impl) { }
GLFW::InputProvider::~InputProvider() = default;

void GLFW::InputProvider::BeginFrame()
{
	_pImpl->UpdateState();
}

void GLFW::InputProvider::EndFrame()
{
}

void GLFW::InputProvider::Terminate()
{
	glfwSetScrollCallback(_pImpl->GlfwWindow, nullptr);
}

KeyboardState const& GLFW::InputProvider::GetKeyboardState() const
{
	return *(_pImpl->CurrentKeyboardState.get());
}

KeyboardState const& GLFW::InputProvider::GetPreviousKeyboardState() const
{
	return *(_pImpl->PreviousKeyboardState.get());
}

MouseState const& GLFW::InputProvider::GetMouseState() const
{
	return *(_pImpl->CurrentMouseState.get());
}

MouseState const& GLFW::InputProvider::GetPreviousMouseState() const
{
	return *(_pImpl->PreviousMouseState.get());
}

/* static stuff ( :((( ) */
static int KeyCodeToGLFWKey(KeyCode keyCode)
{
	struct Temp { KeyCode Key; int Value; bool operator <(const Temp& rhs) const { return Key < rhs.Key; } };
#define CREATE(x, y) Temp { KeyCode::##x##, y }

	// magic value from GLFW docs. Basically map end of all contigous key values to KeyCode, then binary-search
	static const Temp arr[] = {
		CREATE(Space, 32), CREATE(Minus, 45), CREATE(D9, 57), CREATE(Z, 90),
		CREATE(End, 269), CREATE(Pause, 284), CREATE(F12, 301), CREATE(RightSuper, 347) };

	auto start = arr;
	auto end = arr + Array::Length(arr);
	auto found = std::lower_bound(start, end, Temp{ keyCode });
	if (found >= end)
	{
		Logger::LogError("Input.cpp: KeyCodeToGLFWKey: Did you forget to update 'arr'?");
		throw new std::logic_error("Something is wrong. You probably need to update 'arr'");
	}

	int index = found->Value;
	return index - (static_cast<int>(found->Key) - static_cast<int>(keyCode));
}

// okay. what is this? Basically, GLFW doesn't support polling scroll value, but instead only callbacks. and obviously, in C++ you can't subscribe a member-function to a callback that is meant for static callbacks.
// so yeah.. I have to do this instead.. yay...
static int LatestScrollWheelValue = 0;
static void OnScrollWheelCallback(GLFWwindow* window, double xOffset, double yOffset)
{
	LatestScrollWheelValue = static_cast<int>(yOffset);
}

static int GetScrollWheelValue()
{
	int value = LatestScrollWheelValue;
	LatestScrollWheelValue = 0;
	return value;
}