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
		float rotation = _camera.GetRotation();
		const float rotationRad = glm::radians(rotation);
		if (Input::IsKeyPressed(CB_KEY_A))
		{
			position.x -= cos(rotationRad) * _cameraPositionSpeed * timestep.GetSecondsFloat();
			position.y -= sin(rotationRad) * _cameraPositionSpeed * timestep.GetSecondsFloat();
		}
		if (Input::IsKeyPressed(CB_KEY_D))
		{
			position.x += cos(rotationRad) * _cameraPositionSpeed * timestep.GetSecondsFloat();
			position.y += sin(rotationRad) * _cameraPositionSpeed * timestep.GetSecondsFloat();
		}
		if (Input::IsKeyPressed(CB_KEY_W))
		{
			position.x += -sin(rotationRad) * _cameraPositionSpeed * timestep.GetSecondsFloat();
			position.y += cos(rotationRad) * _cameraPositionSpeed * timestep.GetSecondsFloat();
		}
		else if (Input::IsKeyPressed(CB_KEY_S))
		{
			position.x -= -sin(rotationRad) * _cameraPositionSpeed * timestep.GetSecondsFloat();
			position.y -= cos(rotationRad) *_cameraPositionSpeed * timestep.GetSecondsFloat();
		}
		_camera.SetPosition(position);

		if (_rotation) {
			if (Input::IsKeyPressed(CB_KEY_Q))
				rotation += _cameraRotationSpeed * timestep.GetSecondsFloat();
			if (Input::IsKeyPressed(CB_KEY_E))
				rotation -= _cameraRotationSpeed * timestep.GetSecondsFloat();

			if (rotation > 180.0f)
				rotation -= 360.0f;
			else if (rotation <= -180.0f)
				rotation += 360.0f;
			
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
