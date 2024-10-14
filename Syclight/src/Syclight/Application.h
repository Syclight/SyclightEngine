#pragma once

#ifndef __SYC_APPLICATION_H__

#include "Window.h"
#include "Syclight/LayerStack.h"
#include "Syclight/Events/Event.h"
#include "Syclight/Events/ApplicationEvent.h"


#include "Syclight/ImGui/ImGuiLayer.h"

#include "Syclight/Renderer/Shader.h"
#include "Syclight/Renderer/VertexArray.h"
#include "Syclight/Renderer/Buffer.h"
#include "Syclight/Renderer/OrthographicCamera.h"

namespace syc
{
	class SYC_API Application
	{
	private:
		std::unique_ptr<SycWindow> m_Window;
		ImGuiLayer* m_ImGuiLayer = nullptr;
		bool8 m_Running = true;
		LayerStack m_LayerStack;

		std::shared_ptr<VertexArray> m_VertexArray;
		std::shared_ptr<Shader> m_Shader;
		
		std::shared_ptr<VertexArray> m_SquareVA;
		std::shared_ptr<Shader> m_SquareShader;

		OrthographicCamera m_Camera;

		static Application* s_Instance;
	private:
		bool8 OnWindowClose(WindowCloseEvent& e);

	public:
		Application();
		~Application();

		// void_ Start();
		void_ Run();

		void_ OnEvent(Event& e);

		void_ PushLayer(Layer* layer);
		void_ PushOverlay(Layer* layer);

		inline static Application& Get() { return *s_Instance; }
		inline SycWindow& GetWindow() { return *m_Window; }
	};

	// 客户端API
	Application* CreateApplication();
}

#endif // !__SYC_APPLICATION_H__