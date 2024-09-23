#include <Syclight.h>

class SandboxApp : public syc::Application
{
public:
	SandboxApp()
	{

	}

	~SandboxApp()
	{

	}
};

syc::Application* syc::CreateApplication()
{
	syc::Application* app = nullptr;
	app = new syc::Application();
	return app;
}