#pragma once
#include <Graphics\IGraphicsContext.h>
#include <Graphics\OpenGL\OGL.h>

namespace OGL
{
	// must be inside namespace
	class GameWindow;

	// okay I'm having a bit of a "fuck that" feelings atm.. So basically, don't focus so much on the portability/abstractness, just get it done!
	class GraphicsContext : public IGraphicsContext
	{
	public:

		// depth stuff
		virtual bool IsDepthTestEnabled() const override;
		virtual void SetDepthTestEnabled(bool isEnabled) override;
		virtual CompareFunction GetDepthFunction() const override;
		virtual void SetDepthFunction(CompareFunction compareFunction) override;

		// cull stuff
		virtual CullMode GetCullMode() const override;
		virtual void SetCullMode(CullMode cullMode) override;
		virtual CullFace GetCullFace() const override;
		virtual void SetCullFace(CullFace cullFace) override;

		virtual bool IsCullingEnabled() const override;
		virtual void SetCullingEnabled(bool enabled) override;

		// clear
		virtual void Clear(const Color& color) override;
		virtual void Clear(const ClearOptions& clearOptions, const Color& color, float depth = 0, int stencilValue = 0) override;

		// miscp
		virtual Size GetResolution() const override;
		virtual void ChangeResolution(const Size& newSize) override;

		// draw
		virtual void DrawPrimitives(PrimitiveType primitiveType, int firstIndex, int count) override;

		// create
		virtual std::unique_ptr<ITexture2D> CreateTexture2D(std::unique_ptr<Image> textureData) override;
		virtual std::unique_ptr<IVertexBuffer> CreateVertexBuffer(BufferType bufferType) override;
		virtual std::unique_ptr<IShader> CreateShader(const ShaderSource& shaderData) override;

		/* IMPLEMENTATION SPECIFIC */
		GraphicsContext(GameWindow& window);
		virtual ~GraphicsContext() override;

		void ResetViewport() const;

	private:

		// todo: Pimpl?
		// okay.. these default values are not good since if the user (or more like, me, the engine coder) forgets to set the values when constructing GraphicsModule, then these won't be the actual values
		bool _isDepthTestEnabled = false;
		CompareFunction _depthCompareFunction = static_cast<CompareFunction>(-1);
		CullMode _cullMode = static_cast<CullMode>(-1);
		CullFace _cullFace = static_cast<CullFace>(-1);
		bool _isCullingEnabled = false;

		GameWindow& _window;
	};
}