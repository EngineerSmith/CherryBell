#pragma once
//For use by CherryBell Applications

#include "core/Core.h"
#include "core/Application.h"

// ----- Events ------------------------
#include "core/events/Event.h"
#include "core/events/ApplicationEvent.h"
#include "core/events/KeyEvent.h"
#include "core/events/MouseEvent.h"
// -------------------------------------

// ----- Math --------------------------
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define TO_RAD(degrees) ::glm::radians(degrees)
// -------------------------------------

// ----- Debugging ---------------------
#include "core/Log.h"
// -------------------------------------

// ----- Layers ------------------------
#include "core/layer/LayerStack.h"
#include "core/layer/Layer.h"

#include "core/Timestep.h"
// -------------------------------------

// ----- Render API --------------------
#include "core/renderer/Renderer.h"
#include "core/renderer/Renderer2D.h"
#include "core/renderer/RenderCommand.h"
#include "core/renderer/RendererID.h"
#include "core/renderer/DrawType.h"

#include "core/renderer/Buffer.h"
#include "core/renderer/Shader.h"
#include "core/renderer/Texture.h"
#include "core/renderer/VertexArray.h"

#include "core/renderer/OrthorgraphicCamera.h"

#include "core/tilemap/Tilemap.h"
// -------------------------------------

// ----- GUI ---------------------------
#include <imgui.h>
// -------------------------------------

// ----- Input -------------------------
#include "core/input/Input.h"
#include "core/input/KeyCodes.h"
#include "core/input/MouseButtonCodes.h"

#include "core/input/OrthorgraphicCameraController.h"
// -------------------------------------

// ----- Entry Point -------------------
// Define CB_ENTRYPOINT in your project where you define the CreateApplication function
#ifdef CB_ENTRYPOINT
	#include "core/EntryPoint.h"
#endif
// -------------------------------------
