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
	return new SandboxApp();
}