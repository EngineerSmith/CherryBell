#include "cbpch.h"
#include "OrthorgraphicCamera.h"
#include "core/Application.h"

#include <glm/gtc/matrix_transform.hpp>

namespace CherryBell {
	OrthorgraphicCamera::OrthorgraphicCamera(float left, float right, float bottom, float top)
		: _projectionMatrix(glm::ortho(left, right, bottom, top, -1.0f, 1.0f)), _viewMatrix(1.0f)
	{ 
		_viewProjectionMatrix = _projectionMatrix * _viewMatrix;
	}

	void OrthorgraphicCamera::SetProjection(float left, float right, float bottom, float top)
	{
		_projectionMatrix = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
		_viewProjectionMatrix = _projectionMatrix * _viewMatrix;
	}

	void OrthorgraphicCamera::SetPosition(const glm::vec3& position)
	{
		_position = position; 
		RecalculateMatices(); 
	}

	void OrthorgraphicCamera::SetRotation(float rotation) 
	{
		_rotation = rotation; 
		RecalculateMatices(); 
	}

	//TODO add min & max params
CB_COMPILER_WARNING(0001, "OrthorgraphicCamera only supported hardcoded min and max values")
	bool OrthorgraphicCamera::InsideCameraView(const glm::vec3& position, const glm::vec2& size) const
	{
		glm::vec2 min = {-0.5f, -0.5f}, max = {0.5f, 0.5f};

		const glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), glm::vec3(size, 1));
		const glm::mat4 viewProjectionTransformMatrix = _viewProjectionMatrix * transform;

		const auto lam = [](const glm::vec4& r)
		{
			for(int i = 0; i < 3; i++)
				if (r[i] <= 0.0f || r[i] >= 1.0f)
					return false;
			return true;
		};

		if (!lam(viewProjectionTransformMatrix * glm::vec4(min, 0, 1)))
			return false;
		if (!lam(viewProjectionTransformMatrix * glm::vec4(max.x, min.y, 0, 1)))
			return false;
		if (!lam(viewProjectionTransformMatrix * glm::vec4(max, 0, 1)))
			return false;
		if (!lam(viewProjectionTransformMatrix * glm::vec4(min.x, max.y, 0, 1)))
			return false;

		return true;
	}

	void OrthorgraphicCamera::RecalculateMatices()
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), _position) *
									glm::rotate(glm::mat4(1.0f), glm::radians(_rotation), glm::vec3(0,0,1));
	
		_viewMatrix = glm::inverse(transform);
		_viewProjectionMatrix = _projectionMatrix * _viewMatrix;
	}
}
