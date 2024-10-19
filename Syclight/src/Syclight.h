#pragma once

// Syclight Engine Header File 
// For use by applications

#ifndef __SYC_SYCLIGHT_H__
#define __SYC_SYCLIGHT_H__

#include <stdio.h>

#include "Syclight/Core/Common.h"

#include "Syclight/Core/Application.h"
#include "Syclight/Core/Layer.h"
#include "Syclight/Core/Log.h"

#include "Syclight/Core/Timestep.h"

#include "Syclight/Core/Input.h"
#include "Syclight/Core/KeyCodes.h"
#include "Syclight/Core/MouseButtonCodes.h"

#include "Syclight/ImGui/ImGuiLayer.h"

//---Renderer--------------------------------------------
#include "Syclight/Renderer/Renderer.h"
#include "Syclight/Renderer/RenderCommand.h"

#include "Syclight/Renderer/Buffer.h"
#include "Syclight/Renderer/Shader.h"
#include "Syclight/Renderer/Texture.h"
#include "Syclight/Renderer/VertexArray.h"

#include "Syclight/Renderer/OrthographicCamera.h"
#include "Syclight/Renderer/OrthographicCameraController.h"
//-------------------------------------------------------

//---EntryPort-------------------------------------------
#include "Syclight/Core/EntryPoint.h"
//-------------------------------------------------------


//---宏定义-----------------------------------------------
#define   I32       syc::int32
#define   UI32      syc::uint32
#define   F32     syc::float32

//-------------------------------------------------------
#endif // !__SYC_SYCLIGHT_H__
