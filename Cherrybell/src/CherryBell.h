#pragma once
//For use by CherryBell Applications

#include "core/Core.h"
#include "core/Application.h"
#include "core/Timestep.h"

// ----- Math --------------------------
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
// -------------------------------------


// ----- Debugging ---------------------
#include "core/Log.h"
// -------------------------------------

// ----- Layers ------------------------
#include "core/layer/LayerStack.h"
#include "core/layer/Layer.h"
// -------------------------------------

// ----- Render API --------------------
#include "core/renderer/Renderer.h"
#include "core/renderer/RenderCommand.h"
#include "core/renderer/RendererID.h"

#include "core/renderer/Buffer.h"
#include "core/renderer/Shader.h"
#include "core/renderer/VertexArray.h"

#include "core/renderer/OrthorgraphicCamera.h"
// -------------------------------------

// ----- GUI ---------------------------
#include <imgui.h>
// -------------------------------------

// ----- Input -------------------------
#include "core/input/Input.h"
#include "core/input/KeyCodes.h"
#include "core/input/MouseButtonCodes.h"
// -------------------------------------

// ----- Entry Point -------------------
#include "core/EntryPoint.h"
// -------------------------------------
