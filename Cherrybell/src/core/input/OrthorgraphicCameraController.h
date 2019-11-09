#pragma once
#include "core/renderer/OrthorgraphicCamera.h"
#include "core/TimeStep.h"
#include "core/events/ApplicationEvent.h"
#include "core/events/MouseEvent.h"

namespace CherryBell {
	class OrthorgraphicCameraController
	{
	public:
		OrthorgraphicCameraController(float aspectRatio, bool rotation = false);

		OrthorgraphicCamera& GetCamera() { return _camera; }
		const OrthorgraphicCamera& GetCamera() const { return _camera; }

		void OnUpdate(Timestep timestep);
		void OnEvent(Event& event);
	private:
		bool OnMouseScrolled(MouseScrolledEvent& event);
		bool OnWindowResize(WindowResizedEvent& event);
	private:
		float _aspectRatio, _zoomLevel = 1.0f;
		OrthorgraphicCamera _camera;

		bool _rotation;
		const float _cameraPositionSpeed = 1.5f, _cameraRotationSpeed = 45.0f, _cameraZoomSpeed = 0.5f;
	};
}
