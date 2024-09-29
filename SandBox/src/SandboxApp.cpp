#include <Syclight.h>

class ExampleLayer : public syc::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{
	}

	void OnUpdate() override
	{
		SYC_INFO("ExampleLayer::Update");
	}

	void OnEvent(syc::Event& e) override
	{
		 SYC_TRACE("{0}", e);
	}
};

class Sandbox : public syc::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
		PushLayer(new syc::ImGuiLayer());
	}

	~Sandbox()
	{

	}
};

syc::Application* syc::CreateApplication()
{
	return new Sandbox();
}