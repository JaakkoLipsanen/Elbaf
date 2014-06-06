#pragma once
#include <Core\Common.h>
class Game;

class InputManager
{
	friend Game;
	InputManager();

	void Initialize();
	void Update();
	void OnFrameEnded();
public:
	~InputManager();
};

// Okay.. I decided to map the values directly to GLFW values... Not very clean etc but whatever
enum class KeyCode
{
	Space = 0,
	Minus,

	D0,
	D1, 
	D2,
	D3,
	D4,
	D5,
	D6,
	D7,
	D8,
	D9,

	A,
	B,
	C,
	D,
	E,
	F,
	G,
	H,
	I,
	J,
	K,
	L,
	M,
	N,
	O,
	P,
	Q,
	R,
	S,
	T,
	U,
	V,
	W,
	X,
	Y,
	Z,

	Escape,
	Enter,
	Tab,
	Backspace,
	Insert,
	Delete,
	Right,
	Left,
	Down,
	Up,
	PageUp,
	PageDown,
	Home,
	End,
	CapsLock,
	ScrollLock,
	NumLock,
	PrintScreen,
	Pause,

	F1,
	F2,
	F3,
	F4,
	F5,
	F6,
	F7,
	F8,
	F9,
	F10,
	F11,
	F12,

	LeftShift,
	LeftControl,
	LeftAlt,
	LeftSuper,
	RightShift,
	RightControl,
	RightAlt,
	RightSuper,
};

enum class MouseButton
{
	Left = 0,
	Right = 1,
	Middle = 2,
};

namespace Input
{
	// TODO: add events!  glfwSetKeyCallback, glfwSetCharCallback, glfwSetMouseButtonCallback etc etc
	// todo: make Vector2 class and then add MousePosition, PreviousMousePos & MouseDelta
	bool IsKeyPressed(KeyCode keyCode);
	bool WasKeyPressed(KeyCode keyCode);
	bool IsNewKeyPress(KeyCode keyCode);

	bool IsMouseButtonPressed(MouseButton mouseButton);
	bool WasMouseButtonPressed(MouseButton mouseButton);
	bool IsNewMouseButtonPress(MouseButton mouseButton);

	bool IsMouseInsideWindow();

	float GetScrollWheelDelta();

	Vector2f GetMousePosition();
	Vector2f GetPreviousMousePosition();
	Vector2f GetMousePositionDelta();
	// todo: scroll delta
}