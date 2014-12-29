
#include <Engine/DebugConsole.h>
#include <Graphics/SpriteBatch.h>
#include <Engine/Game.h>
#include <Math/FlaiMath.h>
#include <Engine/Time.h>
#include <Engine\Screen.h>

#include <Graphics/TextureHelper.h>
#include <Input\Input.h>
#include <Input\KeyCode.h>

#include <Graphics\Font.h>
#include <Content\Content.h>
#include <Core\File.h>


// TODO: Separate DebugConsoleRenderer to different class !! Renderer should probably be completely independent? Though I think it's cleanest if DebugConsole itself owns the renderer
enum class ConsoleState
{
	Open,
	Peeking,
	Hidden,
};

static float GetTargetHeight(ConsoleState state)
{
	if (state == ConsoleState::Hidden)
	{
		return 0;
	}
	else if (state == ConsoleState::Peeking)
	{
		return 40;
	}
	else // "Open"
	{
		return 240;
	}
}

static ConsoleState AdvanceState(ConsoleState state)
{
	if (state == ConsoleState::Hidden)
	{
		return ConsoleState::Open;
	}
	else if (state == ConsoleState::Open)
	{
		return ConsoleState::Peeking;
	}
	else // Peeking
	{
		return ConsoleState::Hidden;
	}
}

static ConsoleState GetInitialState()
{
#if DEBUG
	return ConsoleState::Peeking;
#endif

	return ConsoleState::Hidden;
}

class DebugConsole::Impl
{
public:
	explicit Impl(Game& game) :
		Game(game), State(GetInitialState())
	{
	}

	Game& Game;
	ConsoleState State;
	std::unique_ptr<SpriteBatch> SpriteBatch;
	std::unique_ptr<Texture2D> BlankPixel;
	float CurrentHeight;

	std::unique_ptr<Font> Font;

	void DrawFPS()
	{
		int fps = static_cast<int>(Time::GetTotalTime()) % 2 + 59;

		Color color = (fps < 60) ? Color::PaleVioletRed : Color::White;
		this->SpriteBatch->DrawText(*this->Font, std::to_string(fps), Vector2f(Screen::GetWidth() - 2, this->CurrentHeight - 22), color, TextCorner::BottomRight);
	}
};

DebugConsole::DebugConsole(Game& game) :
	_pImpl(new Impl(game))
{
}

DebugConsole::~DebugConsole() = default;

void DebugConsole::LoadContent()
{
	_pImpl->SpriteBatch.reset(new SpriteBatch(_pImpl->Game.GetGraphicsContext()));
	_pImpl->BlankPixel = TextureHelper::CreateBlankTexture(_pImpl->Game.GetGraphicsContext());
	_pImpl->Font = Content::LoadFont(_pImpl->Game.GetGraphicsContext(), File::GetAbsolutePath("Fonts/ConsolasBold.ttf"), 20);
}

void DebugConsole::Update()
{
	_pImpl->CurrentHeight = FlaiMath::Lerp(_pImpl->CurrentHeight, GetTargetHeight(_pImpl->State), Time::GetDeltaTime() * 8);
	if (Input::IsNewKeyPress(KeyCode::Tab))
	{
		_pImpl->State = AdvanceState(_pImpl->State);
	}
}

void DebugConsole::Render()
{
	if (_pImpl->CurrentHeight <= 0)
	{
		return;
	}

	_pImpl->SpriteBatch->Begin();
	_pImpl->SpriteBatch->Draw(*_pImpl->BlankPixel, Vector2f::Zero, Color::Black * 0.45f, 0, Vector2f(Screen::GetWidth(), _pImpl->CurrentHeight));
	_pImpl->SpriteBatch->DrawText(*_pImpl->Font, _pImpl->Game.GetTitle(), Vector2f(Screen::GetWidth() - 2, _pImpl->CurrentHeight - 2), Color::White * 0.75f, TextCorner::BottomRight);
	_pImpl->DrawFPS();
	_pImpl->SpriteBatch->End();
}