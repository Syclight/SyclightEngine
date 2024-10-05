#include <Syclight.h>

//#include "imgui/imgui.h"

class ExampleLayer : public syc::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{
	}

	void OnUpdate() override
	{
		if (syc::Input::IsKeyPressed(SYC_KEY_TAB))
		{
			SYC_TRACE("Tab key is pressed (poll)!");
		}
		// SYC_INFO("ExampleLayer::Update");
	}

	void OnImGuiRender() override
	{
		/*ImGui::Begin("Test");
		ImGui::Text("Hi! This is Syclight Engine.");
		ImGui::End();*/
	}

	void OnEvent(syc::Event& e) override
	{
		 //SYC_TRACE("{0}", e);
		if (e.GetEventType() == syc::EventType::KeyPressed)
		{
			syc::KeyPressedEvent kpe = (syc::KeyPressedEvent&)e;
			if (kpe.GetKeyCode() == SYC_KEY_TAB)
				SYC_TRACE("Tab key is pressed (event)!");
		}
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
	return new Sandbox();
}