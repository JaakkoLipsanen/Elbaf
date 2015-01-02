#pragma once
#include <memory>
#include <Core\Event.h>
#include <Core\IEngine.h>

class Scene;
class IGameWindow;
class GraphicsContext;
struct WindowDescription;

class Game : public IEngine
{
public:
	Event<void()> BeginFrame = Event<void()>();
	Event<void()> EndFrame = Event<void()>();
	Event<void()> Exiting = Event<void()>();

	explicit Game(std::string title = "Elbaf");
	virtual ~Game();

	void Run();
	void Exit();
	IGameWindow& GetWindow() const override;
	GraphicsContext& GetGraphicsContext() const;

	std::string GetTitle() const;

	static Game& GetInstance();

protected:
	virtual void Initialize() { }
	virtual void PreUpdate() { }
	virtual void PostUpdate() { }
	virtual void PreRender() { }
	virtual void PostRender() { }
	virtual void OnExiting() { }

	virtual std::unique_ptr<Scene> CreateDefaultScene() = 0;
	virtual void SetupWindow(WindowDescription& description) { } // should this be forced to be implemented (pure virtual)?
	virtual IModule& GetModuleInner(const type_info& typeInfo) const override;

private:
	class Impl;
	std::unique_ptr<Impl> _pImpl;
};