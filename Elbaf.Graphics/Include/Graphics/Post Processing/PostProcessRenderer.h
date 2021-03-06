#pragma once
#include <vector>
#include <Graphics/GraphicsContext.h>

class ICamera;
class PostProcessRenderer
{
	friend class PostProcess;

public:
	explicit PostProcessRenderer(GraphicsContext& graphicsContext);
	~PostProcessRenderer();

	template<typename T>
	T* Get()
	{
		static_assert(std::is_base_of<PostProcess, T>::value, "Type must inherit from PostProcess!");

		for (auto& postProcess : _postProcesses)
		{
			T* p = dynamic_cast<T*>(postProcess.get());
			if (p != nullptr) return p;
		}

		return nullptr;
	}


	std::shared_ptr<PostProcess> AddPostProcess(std::shared_ptr<PostProcess> postProcess);
	void Update();
	void BeginRender();
	void Render(const ICamera* renderCamera);

	// TODO: REMOVE
	void DrawFullscreen(RenderTarget& r);

private:
	GraphicsContext& _graphicsContext;
	std::vector<std::shared_ptr<PostProcess>> _postProcesses;

	std::unique_ptr<VertexBuffer> _quadVertexBuffer;
	std::unique_ptr<RenderTarget> _currentRenderTarget; // this always contains the scene/preveious post process
	std::unique_ptr<RenderTarget> _backgroundRenderTarget;
	std::unique_ptr<Shader> _passthroughShader;
};