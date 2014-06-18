#pragma once
#include <Graphics\IShader.h>
#include <Graphics\OpenGL\OGL.h>
#include <string>
#include <memory>

namespace OGL
{
	class Shader : public IShader
	{
	public:
		static std::unique_ptr<IShader> Load(const std::string& vertexFilePath, const std::string& fragmentFilePath);

		virtual void ApplyShader() override;
		virtual ~Shader() override;

		// parameter setters
		virtual void SetParameter(std::string const& valueName, float const& value) override;
		virtual void SetParameter(std::string const& valueName, Vector2f const& value) override;
		virtual void SetParameter(std::string const& valueName, Vector3f const& value) override;
		virtual void SetParameter(std::string const& valueName, Vector4f const& value) override;
		virtual void SetParameter(std::string const& valueName, int const& value) override;
		virtual void SetParameter(std::string const& valueName, Vector2i const& value) override;
		virtual void SetParameter(std::string const& valueName, Vector3i const& value) override;
		virtual void SetParameter(std::string const& valueName, Vector4i const& value) override;
		virtual void SetParameter(std::string const& valueName, Matrix2x2 const& value) override;
		virtual void SetParameter(std::string const& valueName, Matrix3x3 const& value) override;
		virtual void SetParameter(std::string const& valueName, Matrix4x4 const& value) override;

	protected:
		virtual float GetFloat(std::string const& valueName) const override;
		virtual Matrix4x4 GetMatrix4x4(std::string const& valueName) const override;

	private:
		class PImpl;
		std::unique_ptr<PImpl> _pImpl;

		explicit Shader(PImpl* pImpl);
	};
}