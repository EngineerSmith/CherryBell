#pragma once
#include <CherryBell.h>

class Sandbox2D : public CherryBell::Layer
{
public:
	Sandbox2D();

	void OnAttach() override;

	void OnUpdate() override;
	void OnRender() override;
	void OnImGuiRender() override;
	void OnEvent(CherryBell::Event& event) override;
private:
	CherryBell::OrthorgraphicCameraController _cameraController;
	
	CherryBell::Ref<CherryBell::Texture2D> _texture;

	glm::vec3 _quadColor = glm::vec3(1);
};