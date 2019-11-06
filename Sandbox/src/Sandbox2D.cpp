#include "Sandbox2D.h"

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), _cameraController(1280.0f / 720.0f, true), 
	_texture(CherryBell::Texture2D::Create("assets/textures/icecream.png"))
{ }

void Sandbox2D::OnAttach()
{ }

void Sandbox2D::OnUpdate()
{
	_cameraController.OnUpdate(DELTATIME);
}

void Sandbox2D::OnRender()
{
	CherryBell::RenderCommand::SetClearColor({ 1.0, 0.0, 1.0, 1.0 });
	CherryBell::RenderCommand::Clear();

	CherryBell::Renderer2D::BeginScene(_cameraController.GetCamera());
	CherryBell::Renderer2D::FillQuad({ 0.5f,0 }, { 0.5f,0.5f }, TO_RAD(45.0f), { _quadColor*0.5f,1 });
	CherryBell::Renderer2D::FillQuad({ 0,0 }, { 0.5f,0.5f }, 0, { _quadColor,1 });
	CherryBell::Renderer2D::FillQuad({ -0.5f,0 }, { 0.5f,0.5f }, TO_RAD(237.0f), { _quadColor*2.0f,1 });
	
	CherryBell::Renderer2D::FillQuad({ 0,-0.0f,-0.1f }, { 2.5f,2.5f }, 0, { _quadColor,1 }, _texture);
	CherryBell::Renderer2D::FillQuad({ 0,-0.65f }, { 0.5f,0.5f }, 0, _texture);
	
	CherryBell::Renderer2D::EndScene();
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
