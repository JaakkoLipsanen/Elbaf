#pragma once
#include <Graphics/IGraphicsContext.h>
#include "RenderTarget.h"
#include <vector>
#include <Graphics/VertexFormats.h>

class PostProcessRenderer
{
	friend class PostProcess;

public:
	explicit PostProcessRenderer(IGraphicsContext& graphicsContext);

	void AddPostProcess(std::shared_ptr<PostProcess> postProcess);
	void BeginRender();
	void Render();

private:
	IGraphicsContext& _graphicsContext;
	std::vector<std::shared_ptr<PostProcess>> _postProcesses;

	std::unique_ptr<IVertexBuffer> _quadVertexBuffer;
	std::unique_ptr<RenderTarget> _currentRenderTarget; // this always contains the scene/preveious post process
	std::unique_ptr<RenderTarget> _backgroundRenderTarget;
	std::unique_ptr<IShader> _passthroughShader;
};