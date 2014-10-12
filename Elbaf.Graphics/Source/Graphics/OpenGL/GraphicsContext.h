#pragma once
#include <Graphics\IGraphicsContext.h>
#include <Graphics\OpenGL\OGL.h>
#include <Core\Color.h>
#include <Graphics\OpenGL\BlendState.h>
#include <Graphics\OpenGL\DepthState.h>
#include <Graphics\OpenGL\CullState.h>

class IBlendState;
namespace OGL
{
	// must be inside namespace
	class GameWindow;

	// okay I'm having a bit of a "fuck that" feelings atm.. So basically, don't focus so much on the portability/abstractness, just get it done!
	class GraphicsContext : public IGraphicsContext
	{
	public:

		// depth stuff
		virtual IDepthState& GetDepthState() override;
		virtual void SetDepthState(DepthStatePreset const& depthStatePreset) override;

		// cull stuff
		virtual ICullState& GetCullState() override;
		virtual void SetCullState(CullStatePreset const& preset) override;

		// blend ( jesus christ )
		virtual IBlendState& GetBlendState() override;
		virtual void SetBlendState(const BlendStatePreset& blendStatePreset) override;

		// clear
		virtual void Clear(const Color& color) override;
		virtual void Clear(const ClearOptions& clearOptions, const Color& color, float depth = 0, int stencilValue = 0) override;
		
		// miscp
		virtual Size GetResolution() const override;
		virtual void ChangeResolution(const Size& newSize) override;

		// draw
		virtual void DrawPrimitives(PrimitiveType primitiveType, int firstIndex, int count) override;

		// create
		virtual std::unique_ptr<ITexture2D> CreateTexture2D(const Image& textureData) override;
		virtual std::unique_ptr<IVertexBuffer> CreateVertexBuffer(BufferType bufferType) override;
		virtual std::unique_ptr<IShader> CreateShader(const ShaderSource& shaderData) override;
		virtual std::unique_ptr<IBlendState> CreateBlendState() override;

		/* IMPLEMENTATION SPECIFIC */
		GraphicsContext(GameWindow& window);
		virtual ~GraphicsContext() override;

		void ResetViewport() const;

	private:

		class Impl;
		std::unique_ptr<Impl> _pImpl;

		BlendState _blendState;
		DepthState _depthState;
		CullState _cullState;
		GameWindow& _window;
	};
}