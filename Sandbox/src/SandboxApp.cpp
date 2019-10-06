#include <CherryBell.h>

class ExampleLayer : public CherryBell::Layer
{
public:
	ExampleLayer() 
		: Layer("Example"), _camera(-1.6f, 1.6f, -0.9f, 0.9f)
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

			out vec3 v_position;
			out vec4 v_color;

			void main()
			{
				v_position = a_position;
				v_color = a_color;
				gl_Position = u_viewProjection * vec4(a_position,1.0);
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 _color;
			
			in vec3 v_position;
			in vec4 v_color;

			void main()
			{
				_color = v_color;
			}
		)";

		_shader = std::make_shared<CherryBell::Shader>(vertexSrc, fragmentSrc);
	}

	void OnUpdate() override
	{
		CherryBell::RenderCommand::SetClearColor({ 1.0, 0.0, 1.0, 1.0 });
		CherryBell::RenderCommand::Clear();

		CherryBell::Renderer::BeginScene(_camera);

		CherryBell::Renderer::Submit(_shader, _vertexArray);

		CherryBell::Renderer::EndScene();
	}

	void OnImGuiRender() override
	{
	}

	void OnEvent(CherryBell::Event& event) override
	{ }
private:
	std::shared_ptr<CherryBell::Shader> _shader;
	std::shared_ptr<CherryBell::VertexArray> _vertexArray;

	CherryBell::OrthorgraphicCamera _camera;
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
