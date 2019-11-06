#include "Sandbox2D.h"

// TEMP
#include "platform/OpenGL/OpenGLShader.h"

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), _cameraController(1280.0f / 720.0f, true)
{ }

void Sandbox2D::OnAttach()
{
	_vertexArray = CherryBell::VertexArray::Create();

	float vertices[] = {
		//a_position	   
		 -0.5f, -0.5f, 0.0f, 
		  0.5f, -0.5f, 0.0f, 
		  0.5f,  0.5f, 0.0f, 
		 -0.5f,  0.5f, 0.0f 
	};
	CherryBell::Ref<CherryBell::VertexBuffer> vertexBuffer = CherryBell::VertexBuffer::Create(vertices, sizeof(vertices));

	CherryBell::BufferLayout layout = {
		{CherryBell::ShaderDataType::Float3, "a_position"}
	};

	vertexBuffer->SetLayout(layout);
	_vertexArray->AddVertexBuffer(vertexBuffer);

	uint32_t indices[] = { 0u,1u,2u, 2u,3u,0u };

	CherryBell::Ref<CherryBell::IndexBuffer> indexBuffer;
	indexBuffer.reset(CherryBell::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
	_vertexArray->SetIndexBuffer(indexBuffer);

	_shaderLibrary.Load("assets/shaders/FlatColor.glsl");
}

void Sandbox2D::OnUpdate()
{
	_cameraController.OnUpdate(DELTATIME);
}

void Sandbox2D::OnRender()
{
	CherryBell::RenderCommand::SetClearColor({ 1.0, 0.0, 1.0, 1.0 });
	CherryBell::RenderCommand::Clear();

	CherryBell::Renderer::BeginScene(_cameraController.GetCamera());

	auto& shader = _shaderLibrary.Get("FlatColor");
	shader->Bind();
	std::dynamic_pointer_cast<CherryBell::OpenGLShader>(shader)->UploadUniformFloat3(_quadColor, "u_color");

	CherryBell::Renderer::Submit(shader, _vertexArray, glm::mat4(1.0f));

	CherryBell::Renderer::EndScene();
}

void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit3("Color", glm::value_ptr(_quadColor));
	ImGui::End();
}

void Sandbox2D::OnEvent(CherryBell::Event& event)
{
	_cameraController.OnEvent(event);
}
