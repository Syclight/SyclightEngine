#include <Syclight.h>
#include <Syclight/Core/EntryPoint.h>

#include "Game.h"

class App : public syc::Application
{
public:
	App()
	{
		//PushLayer(new ExampleLayer());
		PushLayer(new Game());
	}

	~App()
	{
	}
};

syc::Application* syc::CreateApplication()
{
	return new App();
}