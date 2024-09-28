#pragma once

#ifndef __SYC_APPLICATION_H__

#include "Common.h"
#include "Core.h"
#include "Syclight/LayerStack.h"
#include "Syclight/Events/Event.h"
#include "Syclight/Events/ApplicationEvent.h"

#include "Window.h"

namespace syc
{
	class SYC_API Application
	{
	private:
		bool4 OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<SycWindow> m_Window;
		bool4 m_Running = true;
		LayerStack m_LayerStack;

	public:
		Application();
		~Application();

		// void_ Start();
		void_ Run();

		void_ OnEvent(Event& e);

		void_ PushLayer(Layer* layer);
		void_ PushOverlay(Layer* layer);
	};

	// 客户端API
	Application* CreateApplication();
}

#endif // !__SYC_APPLICATION_H__