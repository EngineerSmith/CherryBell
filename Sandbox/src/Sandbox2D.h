#pragma once
#include <CherryBell.h>

class Sandbox2D : public CherryBell::Layer
{
public:
	Sandbox2D();

	void OnAttach() override;
	void OnDetach() override;

	void OnUpdate() override;
	void OnRender() override;
	void OnImGuiRender() override;
	void OnEvent(CherryBell::Event& event) override;
private:
	CherryBell::OrthorgraphicCameraController _cameraController;
	
	// TEMP 
	CherryBell::ShaderLibrary _shaderLibrary;
	CherryBell::Ref<CherryBell::VertexArray> _vertexArray;

	glm::vec3 _quadColor = glm::vec3(1);
};