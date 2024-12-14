#include <Syclight.h>
#include <Syclight/Core/EntryPoint.h>

#include "ExampleLayer.h"
#include "Playground2D.h"

class Sandbox : public syc::Application
{
public:
	Sandbox()
	{
		//PushLayer(new ExampleLayer());
		PushLayer(new Playground2D());
	}

	~Sandbox()
	{
	}
};

syc::Application* syc::CreateApplication()
{
	return new Sandbox();
}