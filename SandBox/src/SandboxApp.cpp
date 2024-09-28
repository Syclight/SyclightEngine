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
		//std::cout << e.GetName() << '\n';
		std::cout << e.ToString() << '\n';
	}
};

class Sandbox : public syc::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{

	}
};

syc::Application* syc::CreateApplication()
{
	/*syc::Application* app = nullptr;
	app = new syc::Application();
	return app;*/
	return new Sandbox();
	//return new syc::Application();
}