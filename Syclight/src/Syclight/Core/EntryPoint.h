#pragma once

#ifndef __SYC_ENTRY_POINT_H__
#define __SYC_ENTRY_POINT_H__

#ifdef SYC_PLATFORM_WINDOWS

extern syc::Application* syc::CreateApplication();

int main(int argc, char** argv)
{
	syc::Log::Init();

	SYC_CORE_WARN("Initialized Log!");
	std::string name = "user";
	SYC_INFO("Hello! {}", name);

	auto app = syc::CreateApplication();
	app->Run();

	delete app;

	return 0;
}
#endif

#endif // !__SYC_ENTRY_POINT_H__
