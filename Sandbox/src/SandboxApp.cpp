#include <CherryBell.h>

class ExampleLayer : public CherryBell::Layer
{
public:
	ExampleLayer() 
		: Layer("Example")
	{}

	void OnUpdate() override
	{
		//CB_INFO("ExampleLayer: Update");
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
		PushOverlay(new CherryBell::ImGuiLayer());
	}
	virtual ~Sandbox() = default;
};

CherryBell::Application* CherryBell::CreateApplication() {
	return new Sandbox();
}
