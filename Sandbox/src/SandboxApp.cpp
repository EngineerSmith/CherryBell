#define CB_ENTRYPOINT
#include <CherryBell.h>
#include "Sandbox2D.h"

class ExampleLayer : public CherryBell::Layer
{
public:
	ExampleLayer() 
		: Layer("Example"), _cameraController(1280.0f / 720.0f, true)
	{}

	void OnAttach() override
	{
		_vertexArray = CherryBell::VertexArray::Create();

		float vertices[] = {
		   //a_position		  //a_texCoord
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
		};
		CherryBell::Ref<CherryBell::VertexBuffer> vertexBuffer = CherryBell::VertexBuffer::Create(vertices, sizeof(vertices));

		CherryBell::BufferLayout layout = {
			{CherryBell::ShaderDataType::Float3, "a_position"},
			{CherryBell::ShaderDataType::Float2, "a_texCoord"}
		};

		vertexBuffer->SetLayout(layout);
		_vertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[] = { 0u,1u,2u, 2u,3u,0u };

		CherryBell::Ref<CherryBell::IndexBuffer> indexBuffer;
		indexBuffer.reset(CherryBell::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		_vertexArray->SetIndexBuffer(indexBuffer);

		auto& shader = _shaderLibrary.Load("assets/shaders/Texture.glsl");

		_texture = CherryBell::Texture2D::Create("assets/textures/icecream.png");

		shader->Bind();
		shader->Set(0, "u_texture");
	}

	void OnUpdate() override
	{ 
		_cameraController.OnUpdate(DELTATIME);

		if (CherryBell::Input::IsKeyPressed(CB_KEY_H))
			_modelPosition.x -= 3.0f * 0.5f * (float)DELTATIME;
		if (CherryBell::Input::IsKeyPressed(CB_KEY_K))
			_modelPosition.x += 3.0f * 0.5f * (float)DELTATIME;
	}

	void OnRender() override
	{
		CherryBell::RenderCommand::SetClearColor({ 1.0, 0.0, 1.0, 1.0 });
		CherryBell::RenderCommand::Clear();

		CherryBell::Renderer::BeginScene(_cameraController.GetCamera());

		auto& shader = _shaderLibrary.Get("Texture");
		shader->Bind();
		shader->Set(_modelColor, "u_color");

		_texture->Bind();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), _modelPosition);
		CherryBell::Renderer::Submit(shader, _vertexArray, transform);

		transform = glm::translate(glm::mat4(1.0f), _modelPosition * -1.0f);
		CherryBell::Renderer::Submit(shader, _vertexArray, transform);

		CherryBell::Renderer::EndScene();
	}

	void OnEvent(CherryBell::Event& event) override
	{
		_cameraController.OnEvent(event);
	}


	void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Color", glm::value_ptr(_modelColor));
		ImGui::End();
	}

private:
	CherryBell::ShaderLibrary _shaderLibrary;
	CherryBell::Ref<CherryBell::VertexArray> _vertexArray;

	CherryBell::Ref<CherryBell::Texture2D> _texture;

	CherryBell::OrthorgraphicCameraController _cameraController;

	glm::vec3 _modelPosition = glm::vec3(1,0,0);
	glm::vec3 _modelColor = glm::vec3(1);
};

class Sandbox : public CherryBell::Application {
public:
	Sandbox()
	{
		//PushLayer(new ExampleLayer());
		PushLayer(new Sandbox2D());
	}
	virtual ~Sandbox() = default;
};

CherryBell::Application* CherryBell::CreateApplication() {
	return new Sandbox();
}
