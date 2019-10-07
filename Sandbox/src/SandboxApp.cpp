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
		_vertexArray.reset(CherryBell::VertexArray::Create());

		float vertices[] = {
		   //a_position		  //a_color
			-0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.5f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.5f, 0.0f, 1.0f, 1.0f,
			 0.0f,  0.5f, 0.0f, 1.0f, 0.5f, 0.0f, 1.0f
		};
		std::shared_ptr<CherryBell::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(CherryBell::VertexBuffer::Create(vertices, sizeof(vertices)));

		CherryBell::BufferLayout layout = {
			{CherryBell::ShaderDataType::Float3, "a_position"},
			{CherryBell::ShaderDataType::Float4, "a_color"}
		};

		vertexBuffer->SetLayout(layout);
		_vertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0u,1u,2u };

		std::shared_ptr<CherryBell::IndexBuffer> indexBuffer;
		indexBuffer.reset(CherryBell::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		_vertexArray->SetIndexBuffer(indexBuffer);

		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_position;
			layout(location = 1) in vec4 a_color;

			uniform mat4 u_viewProjection;
			uniform mat4 u_transform;

			out vec4 v_color;

			void main()
			{
				v_color = a_color;
				gl_Position = u_viewProjection * u_transform * vec4(a_position,1.0);
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 _color;
			
			uniform vec3 u_color;

			in vec4 v_color;

			void main()
			{
				_color = v_color * vec4(u_color,1);
			}
		)";
		
		_shader.reset(CherryBell::Shader::Create(vertexSrc, fragmentSrc));
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
	std::shared_ptr<CherryBell::Shader> _shader;
	std::shared_ptr<CherryBell::VertexArray> _vertexArray;

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
