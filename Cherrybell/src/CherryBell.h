#pragma once
//For use by CherryBell Applications

#include "core/Application.h"


// ----- Debugging ---------------------
#include "core/Log.h"
// -------------------------------------

// ----- Layers ------------------------
#include "core/LayerStack.h"
#include "core/Layer.h"
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
#include "core/Input.h"
#include "core/KeyCodes.h"
#include "core/MouseButtonCodes.h"
// -------------------------------------

// ----- Entry Point -------------------
#include "core/EntryPoint.h"
// -------------------------------------
