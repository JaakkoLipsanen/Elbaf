#pragma once
#include <Graphics/IGraphicsContext.h>
#include "RenderTarget.h"
#include <string>

class ICamera;
class PostProcess
{
	friend class PostProcessRenderer;

public:
	virtual ~PostProcess() { }

	bool IsEnabled() const
	{
		return _enabled;
	}

	void SetEnabled(bool enabled)
	{
		_enabled = enabled;
	}

protected:
	explicit PostProcess(IGraphicsContext& graphicsContext) : _graphicsContext(graphicsContext), _enabled(true) { }
	virtual void LoadContent() { }
	virtual ShaderSource CreateShader(const std::string& defaultVertexShader) = 0;

	// default implementation == draw full screen quad with the shader applied
	virtual void Update() { }
	virtual void Process(RenderTarget& source, RenderTarget& destination, RenderTarget& originalSceneRT, const ICamera* renderCamera);
	IVertexBuffer& GetFullscreenQuadBuffer();
	IShader& GetShader();

	IGraphicsContext& _graphicsContext;

private:
	void Initialize(PostProcessRenderer& parentRenderer);
	void ProcessInner(RenderTarget& source, RenderTarget& destination, RenderTarget& originalSceneRT, const ICamera* renderCamera);

	PostProcessRenderer* _parentRenderer;
	std::unique_ptr<IShader> _shader;
	bool _enabled;
};
