#include <CherryBell.h>

class ExampleLayer : public CherryBell::Layer
{
public:
	ExampleLayer() 
		: Layer("Example")
	{}

	void OnImGuiRender() override
	{
		ImGui::Begin("Heyo");
		ImGui::Text("Hello world");
		ImGui::End();
	}

	void OnEvent(CherryBell::Event& event) override
	{
		CB_TRACE("{0}", event);
	}
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
