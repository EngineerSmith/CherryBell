#include <CherryBell.h>

#include "platform/OpenGL/OpenGLShader.h"

class ExampleLayer : public CherryBell::Layer
{
public:
	ExampleLayer() 
		: Layer("Example"), _camera(-1.6f, 1.6f, -0.9f, 0.9f), _cameraPosition(0)
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

		_shader = CherryBell::Shader::Create("assets/shaders/Texture.glsl");

		_texture = CherryBell::Texture2D::Create("assets/textures/icecream.png");

		_shader->Bind();
		std::dynamic_pointer_cast<CherryBell::OpenGLShader>(_shader)->UploadUniformInt(0, "u_texture");
	}

	void OnUpdate(CherryBell::Timestep timestep) override
	{
		if (CherryBell::Input::IsKeyPressed(CB_KEY_LEFT) || CherryBell::Input::IsKeyPressed(CB_KEY_A))
			_cameraPosition.x -= _cameraSpeedPosition * timestep.GetSeconds();
		if (CherryBell::Input::IsKeyPressed(CB_KEY_RIGHT) || CherryBell::Input::IsKeyPressed(CB_KEY_D))
			_cameraPosition.x += _cameraSpeedPosition * timestep.GetSeconds();
		if (CherryBell::Input::IsKeyPressed(CB_KEY_UP) || CherryBell::Input::IsKeyPressed(CB_KEY_W))
			_cameraPosition.y += _cameraSpeedPosition * timestep.GetSeconds();
		else if (CherryBell::Input::IsKeyPressed(CB_KEY_DOWN) || CherryBell::Input::IsKeyPressed(CB_KEY_S))
			_cameraPosition.y -= _cameraSpeedPosition * timestep.GetSeconds();

		if (CherryBell::Input::IsKeyPressed(CB_KEY_Q))
			_cameraRotation += _cameraSpeedRotation * timestep.GetSeconds();
		if (CherryBell::Input::IsKeyPressed(CB_KEY_E))
			_cameraRotation -= _cameraSpeedRotation * timestep.GetSeconds();

		if (CherryBell::Input::IsKeyPressed(CB_KEY_H))
			_modelPosition.x -= _cameraSpeedPosition * 0.5f * timestep.GetSeconds();
		if (CherryBell::Input::IsKeyPressed(CB_KEY_K))
			_modelPosition.x += _cameraSpeedPosition * 0.5f * timestep.GetSeconds();

		CherryBell::RenderCommand::SetClearColor({ 1.0, 0.0, 1.0, 1.0 });
		CherryBell::RenderCommand::Clear();

		_camera.SetPosition(_cameraPosition);
		_camera.SetRotation(_cameraRotation);

		CherryBell::Renderer::BeginScene(_camera);

		_shader->Bind();
		std::dynamic_pointer_cast<CherryBell::OpenGLShader>(_shader)->UploadUniformFloat3(_modelColor, "u_color");
		
		_texture->Bind();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), _modelPosition);
		CherryBell::Renderer::Submit(_shader, _vertexArray, transform);

		transform = glm::translate(glm::mat4(1.0f), _modelPosition * -1.0f);
		CherryBell::Renderer::Submit(_shader, _vertexArray, transform);

		CherryBell::Renderer::EndScene();
	}

	void OnImGuiRender() override
	{
		ImGui::Begin("Model Settings");
		ImGui::ColorEdit3("Model Color", glm::value_ptr(_modelColor));
		ImGui::End();
	}

private:
	CherryBell::Ref<CherryBell::Shader> _shader;
	CherryBell::Ref<CherryBell::VertexArray> _vertexArray;

	CherryBell::Ref<CherryBell::Texture2D> _texture;

	CherryBell::OrthorgraphicCamera _camera;
	glm::vec3 _cameraPosition;
	float _cameraRotation = 0.0f;
	float _cameraSpeedPosition = 3.0f;
	float _cameraSpeedRotation = 20.0f;

	glm::vec3 _modelPosition = glm::vec3(0);
	glm::vec3 _modelColor = glm::vec3(1);
};

class Sandbox : public CherryBell::Application {
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}
	virtual ~Sandbox() = default;
};

CherryBell::Application* CherryBell::CreateApplication() {
	return new Sandbox();
}
