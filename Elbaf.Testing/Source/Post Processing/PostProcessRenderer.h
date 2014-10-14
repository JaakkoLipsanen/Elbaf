#pragma once
#include <Graphics/IGraphicsContext.h>
#include <vector>
#include <Graphics/VertexFormats.h>
#include <RenderTarget.h>

class ICamera;
class PostProcessRenderer
{
	friend class PostProcess;

public:
	explicit PostProcessRenderer(IGraphicsContext& graphicsContext);

	template<typename T>
	T* Get()
	{
		for (auto& postProcess : _postProcesses)
		{
			T* p = dynamic_cast<T*>(postProcess.get());
			if (p != nullptr) return p;
		}

		return nullptr;
	}

	void Update();
	std::shared_ptr<PostProcess> AddPostProcess(std::shared_ptr<PostProcess> postProcess);
	void BeginRender();
	void Render(const ICamera* renderCamera);

private:
	IGraphicsContext& _graphicsContext;
	std::vector<std::shared_ptr<PostProcess>> _postProcesses;

	std::unique_ptr<IVertexBuffer> _quadVertexBuffer;
	std::unique_ptr<RenderTarget> _currentRenderTarget; // this always contains the scene/preveious post process
	std::unique_ptr<RenderTarget> _backgroundRenderTarget;
	std::unique_ptr<IShader> _passthroughShader;
};