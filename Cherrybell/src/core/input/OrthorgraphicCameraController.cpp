#include "cbpch.h"
#include "OrthorgraphicCameraController.h"

#include "core/input/Input.h"
#include "core/input/KeyCodes.h"

namespace CherryBell {
	OrthorgraphicCameraController::OrthorgraphicCameraController(float aspectRatio, bool rotation)
		: _aspectRatio(aspectRatio), 
		_camera(-_aspectRatio * _zoomLevel, _aspectRatio * _zoomLevel, -_zoomLevel, _zoomLevel), 
		_rotation(rotation)
	{ }

	void OrthorgraphicCameraController::OnUpdate(Timestep timestep)
	{
		glm::vec3 position = _camera.GetPosition();

		if (Input::IsKeyPressed(CB_KEY_A))
			position.x -= _cameraPositionSpeed * timestep.GetSeconds();
		if (Input::IsKeyPressed(CB_KEY_D))
			position.x += _cameraPositionSpeed * timestep.GetSeconds();
		if (Input::IsKeyPressed(CB_KEY_W))
			position.y += _cameraPositionSpeed * timestep.GetSeconds();
		else if (Input::IsKeyPressed(CB_KEY_S))
			position.y -= _cameraPositionSpeed * timestep.GetSeconds();

		_camera.SetPosition(position);

		if (_rotation) {
			float rotation = _camera.GetRotation();

			if (Input::IsKeyPressed(CB_KEY_Q))
				rotation += _cameraRotationSpeed * timestep.GetSeconds();
			if (Input::IsKeyPressed(CB_KEY_E))
				rotation -= _cameraRotationSpeed * timestep.GetSeconds();

			_camera.SetRotation(rotation);
		}
	}

	void OrthorgraphicCameraController::OnEvent(Event& event)
	{
		EventDispatcher dispatch(event);
		dispatch.Dispatch<MouseScrolledEvent>(CB_BIND_EVENT_FN(OrthorgraphicCameraController::OnMouseScrolled));
		dispatch.Dispatch<WindowResizeEvent>(CB_BIND_EVENT_FN(OrthorgraphicCameraController::OnWindowResize));
	}

	bool OrthorgraphicCameraController::OnMouseScrolled(MouseScrolledEvent& event)
	{
		_zoomLevel -= event.GetOffsetY() * _cameraZoomSpeed;
		_zoomLevel = std::max(_zoomLevel, 0.25f);
		_camera.SetProjection(-_aspectRatio * _zoomLevel, _aspectRatio * _zoomLevel, -_zoomLevel, _zoomLevel);
		return true;
	}
	bool OrthorgraphicCameraController::OnWindowResize(WindowResizeEvent& event)
	{
		_aspectRatio = (float)event.GetWidth() / (float)event.GetHeight();
		_camera.SetProjection(-_aspectRatio * _zoomLevel, _aspectRatio * _zoomLevel, -_zoomLevel, _zoomLevel);
		return true;
	}
}