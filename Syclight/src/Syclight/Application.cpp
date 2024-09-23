#include "Application.h"

#include <iostream>

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
		std::cout << "App Start." << std::endl;
	}

	void_ Application::Run()
	{
		while (true)
		{
			std::cout << "running..." << std::endl;
		}
	}
}