#include "Sandbox2D.h"

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), _cameraController(1280.0f / 720.0f, true)
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

	CherryBell::Renderer2D::LineQuad({ 0,0 }, { 1,1 }, { _quadColor,1 });

	CherryBell::Renderer2D::EndScene();

	//TODO: Shader::SetMat4, Shader::SetVec3 - OR Materials
	//auto& shader = _shaderLibrary.Get("FlatColor");
	//shader->Bind();
	//std::dynamic_pointer_cast<CherryBell::OpenGLShader>(shader)->UploadUniformFloat3(_quadColor, "u_color");
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
