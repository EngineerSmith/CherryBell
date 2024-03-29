#include "Sandbox2D.h"

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), _cameraController(1280.0f / 720.0f, true), 
	_texture(CherryBell::Texture2D::Create("assets/textures/icecream.png")),
	_tilemap(1, 1)
{
	_tilemap.GetMap()[std::make_pair<int, int>(0,0)] = std::dynamic_pointer_cast<CherryBell::Tile>(CherryBell::CreateRef<CherryBell::TexturedTile>(_texture));
}

void Sandbox2D::OnAttach()
{ }

void Sandbox2D::OnUpdate()
{
	CB_PROFILE_FUNCTION();
	_cameraController.OnUpdate(DELTATIME);

	if (CherryBell::Input::IsKeyPressed(CB_KEY_N))
		CherryBell::Application::Get().GetWindow().SetWindowMode(CherryBell::WindowMode::Windowed);
	if (CherryBell::Input::IsKeyPressed(CB_KEY_M))
		CherryBell::Application::Get().GetWindow().SetWindowMode(CherryBell::WindowMode::Boarderless);
}

void Sandbox2D::OnRender()
{
	CB_PROFILE_FUNCTION();
	CherryBell::RenderCommand::SetClearColor({ 1.0, 0.0, 1.0, 1.0 });
	CherryBell::RenderCommand::Clear();

	CherryBell::Renderer2D::BeginScene(_cameraController.GetCamera());
	CherryBell::Renderer2D::FillQuad({ 0.5f,0 }, { 0.5f,0.5f }, TO_RAD(45.0f), { _quadColor*0.5f,1 });
	CherryBell::Renderer2D::FillQuad({ 0,0 }, { 0.5f,0.5f }, 0, { _quadColor,1 });
	CherryBell::Renderer2D::FillQuad({ -0.5f,0 }, { 0.5f,0.5f }, TO_RAD(237.0f), { _quadColor*2.0f,1 });
	
	CherryBell::Renderer2D::FillQuad({ 0,-0.0f,-0.1f }, { 2.5f,2.5f }, 0, { _quadColor,1 }, _texture);
	CherryBell::Renderer2D::FillQuad({ 0,-0.65f }, { 0.5f,0.5f }, 0, _texture);
	
	_tilemap.Render();

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
	CB_PROFILE_FUNCTION();
	_cameraController.OnEvent(event);
}
