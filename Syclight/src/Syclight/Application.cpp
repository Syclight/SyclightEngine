#include "sycpch.h"
#include "Application.h"

#include <iostream>

#include "Events/ApplicationEvent.h"
#include "Log.h"

namespace syc
{
	Application::Application()
	{
	}

	Application::~Application()
	{
	}

	void_ Application::Start()
	{
		// std::cout << "App Start." << std::endl;
	}

	void_ Application::Run()
	{
		WindowResizeEvent e(1280, 720);
		SYC_TRACE(e);
		while (true)
		{
			/*std::cout << "running..." << std::endl;*/
		}
	}
}