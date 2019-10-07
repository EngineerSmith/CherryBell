#pragma once
#include "core/renderer/RendererID.h"
#include <string>

namespace CherryBell {
	class Shader
	{
	public:
		virtual ~Shader() = default;

		static Ref<Shader> Create(const std::string& vertexSrc, const std::string& fragmentSrc);

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
	};
}