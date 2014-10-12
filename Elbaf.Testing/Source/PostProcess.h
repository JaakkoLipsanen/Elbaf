#pragma once
#include <Graphics/IGraphicsContext.h>
#include "RenderTarget.h"
#include <string>

class PostProcess
{
	friend class PostProcessRenderer;

public:
	virtual ~PostProcess() { }

protected:
	explicit PostProcess(IGraphicsContext& graphicsContext) : _graphicsContext(graphicsContext) { }
	virtual void LoadContent() { }
	virtual ShaderSource CreateShader(const std::string& defaultVertexShader) = 0;

	// default implementation == draw full screen quad with the shader applied
	virtual void Process(RenderTarget& source, RenderTarget& destination);
	IVertexBuffer& GetFullscreenQuadBuffer();
	IShader& GetShader();

	IGraphicsContext& _graphicsContext;

private:
	void Initialize(PostProcessRenderer& parentRenderer);
	void ProcessInner(RenderTarget& source, RenderTarget& destination);

	PostProcessRenderer* _parentRenderer;
	std::unique_ptr<IShader> _shader;
};
