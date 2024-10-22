#pragma once

#ifndef __SYC_ENTRY_POINT_H__
#define __SYC_ENTRY_POINT_H__

#ifdef SYC_PLATFORM_WINDOWS

extern syc::Application* syc::CreateApplication();

int main(int argc, char** argv)
{
	syc::Log::Init();

	SYC_PROFILE_BEGIN_SESSION("Startup", "SyclightProfile-Startup.json");
	auto app = syc::CreateApplication();
	SYC_PROFILE_END_SESSION();

	SYC_PROFILE_BEGIN_SESSION("Runtime", "SyclightProfile-Runtime.json");
	app->Run();
	SYC_PROFILE_END_SESSION();

	SYC_PROFILE_BEGIN_SESSION("Shutdown", "SyclightProfile-Shutdown.json");
	delete app;
	SYC_PROFILE_END_SESSION();

	return 0;
}
#endif

#endif // !__SYC_ENTRY_POINT_H__
