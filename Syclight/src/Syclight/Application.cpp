#include "sycpch.h"
#include "Application.h"

#include <iostream>

#include "Events/ApplicationEvent.h"
#include "Log.h"

#include <GLFW/glfw3.h>

namespace syc
{
	Application::Application()
	{
		m_Window = std::unique_ptr<SycWindow>(SycWindow::Create());
	}

	Application::~Application()
	{
	}

	//void_ Application::Start()
	//{
	//	// std::cout << "App Start." << std::endl;
	//}

	void_ Application::Run()
	{
		while (m_Running)
		{
			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			m_Window->OnUpdate();
		}
	}
}