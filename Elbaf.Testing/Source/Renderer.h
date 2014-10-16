#pragma once
#include <Graphics/IGraphicsContext.h>
#include <Math/Vector.h>
#include <vector>
#include <Engine/ICamera.h>
#include <Core/Color.h>
#include "Post Processing/PostProcessRenderer.h"

// dont support custom shaders, just "fixed" shaders
enum class MaterialType
{
	Skybox,
	Terrain,
	Normal,
};

struct Material
{
	MaterialType MaterialType;
	std::shared_ptr<ITexture2D> Texture;
	Color Tint;

	explicit Material(std::shared_ptr<ITexture2D> vertexBuffer, Color tint = Color::White, ::MaterialType type = ::MaterialType::Normal)
		: Texture(vertexBuffer), Tint(tint), MaterialType(type)
	{
	}
};

struct Mesh
{
	std::shared_ptr<IVertexBuffer> VertexBuffer;
	explicit Mesh(std::shared_ptr<IVertexBuffer> vertexBuffer) 
		: VertexBuffer(vertexBuffer)
	{	
	}
};

struct RenderObject
{
	std::shared_ptr<Mesh> Mesh;
	std::shared_ptr<Material> Material;

	Vector3f Position;
	Vector3f Rotation;
	Vector3f Scale;

	bool UseCulling;
	bool UseDepth; // use depth read/write?
	int RenderOrder;

	RenderObject(std::shared_ptr<::Mesh> mesh, std::shared_ptr<::Material> material, Vector3f position)
		: Mesh(mesh), Material(material), Position(position), Rotation(Vector3f::Zero), Scale(Vector3f::One), UseCulling(true), UseDepth(true), RenderOrder(0)
	{	
	}
};

struct DirectionalLight
{
	Vector3f Direction;
	explicit DirectionalLight(Vector3f diretion) : Direction(diretion) { }
};

class RenderTarget;
class Renderer
{
public:
	explicit Renderer(IGraphicsContext& graphicsContext);
	~Renderer();

	void AddObject(std::shared_ptr<const RenderObject> renderObject);
	void SetCamera(ICamera* camera);
	void PostUpdate();
	void Render();
	
private:
	std::vector<std::shared_ptr<const RenderObject>> _renderObjects;
	IGraphicsContext& _graphicsContext;
	ICamera* _camera;
	PostProcessRenderer _postProcessRenderer;
	std::unique_ptr<IShader> _terrainShader;
	std::unique_ptr<IShader> _normalShader;
	int _vertexCount;

	IShader& GetShader(MaterialType materialType);
	void RenderScene();
};