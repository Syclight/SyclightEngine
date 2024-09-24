#pragma once

#ifndef __SYC_APPLICATION_H__

#include "Common.h"
#include "Core.h"
#include "Events/Event.h"
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

	private:
		std::unique_ptr<SycWindow> m_Window;
	};

	// 客户端API
	Application* CreateApplication();
	bool4 m_Running = true;

}

#endif // !__SYC_APPLICATION_H__