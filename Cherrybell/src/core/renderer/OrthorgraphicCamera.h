#pragma once
#include <glm/glm.hpp>

namespace CherryBell {
	class OrthorgraphicCamera 
	{
	public:
		OrthorgraphicCamera(float left, float right, float bottom, float top);
		void SetProjection(float left, float right, float bottom, float top);

		void SetPosition(const glm::vec3& position);
		const glm::vec3& GetPosition() const { return _position; }

		void SetRotation(float rotation);
		float GetRotation() const { return _rotation; }


		const glm::mat4& GetProjectionMatrix() const { return _projectionMatrix; }
		const glm::mat4& GetViewMatrix() const { return _viewMatrix; }
		const glm::mat4& GetViewProjectionMatrix() const { return _viewProjectionMatrix; }
	private:
		void RecalculateMatices();
	private:
		glm::mat4 _projectionMatrix;
		glm::mat4 _viewMatrix;
		glm::mat4 _viewProjectionMatrix;

		glm::vec3 _position = glm::vec3(0, 0, 0);
		float _rotation = 0.0f;
	};
}