#pragma once
#include <memory>

#include <Input\KeyCode.h>
#include <Input\IInputProvider.h>
#include <Core\IModule.h>

// okay fuck, it was a mistake making this use PIMPL. I really over-engineered this whole Input module.....
class InputModule : public IModule
{
public:
	explicit InputModule(IEngine& engine);
	virtual IInputProvider& GetInputProvider();

	virtual void BeginFrame() override;
	virtual void EndFrame() override;

	virtual void Initialize() override;
	virtual void Terminate() override;

private:
	std::unique_ptr<IInputProvider> _inputProvider;
};