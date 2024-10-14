#pragma once

// Syclight Engine Header File 
// For use by applications

#ifndef __SYC_SYCLIGHT_H__
#define __SYC_SYCLIGHT_H__

#include <stdio.h>

#include "Syclight/Common.h"

#include "Syclight/Application.h"
#include "Syclight/Layer.h"
#include "Syclight/Log.h"

#include "Syclight/Input.h"
#include "Syclight/KeyCodes.h"
#include "Syclight/MouseButtonCodes.h"

#include "Syclight/ImGui/ImGuiLayer.h"

//---Renderer--------------------------------------------
#include "Syclight/Renderer/Renderer.h"
#include "Syclight/Renderer/RenderCommand.h"

#include "Syclight/Renderer/Buffer.h"
#include "Syclight/Renderer/Shader.h"
#include "Syclight/Renderer/VertexArray.h"

#include "Syclight/Renderer/OrthographicCamera.h"
//-------------------------------------------------------

//---EntryPort-------------------------------------------
#include "Syclight/EntryPoint.h"
//---EntryPort-------------------------------------------

#endif // !__SYC_SYCLIGHT_H__
