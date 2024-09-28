#pragma once

#ifndef __SYC_APPLICATION_H__

#include "Common.h"
#include "Core.h"
#include "Events/Event.h"
#include "Events/ApplicationEvent.h"

#include "Window.h"

namespace syc
{
	class SYC_API Application
	{
	public:
		Application();
		~Application();

		// void_ Start();
		void_ Run();

		void_ OnEvent(Event& e);
	private:
		bool4 OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<SycWindow> m_Window;
		bool4 m_Running = true;
	};

	// 客户端API
	Application* CreateApplication();
}

#endif // !__SYC_APPLICATION_H__