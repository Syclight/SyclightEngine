#pragma once

#ifndef __SYC_ENTRY_POINT_H__
#define __SYC_ENTRY_POINT_H__

extern syc::Application* syc::CreateApplication();

int main(int argc, char** argv)
{
	syc::Log::Init();
	SYC_LOG_ENGINE_WARN("Initialized Log!");
	int16 a = 5;
	SYC_LOG_INFO("Hello! Var={0}", a);

	auto app = syc::CreateApplication();
	app->Run();
	delete app;
	return 0;
}

#endif // !__SYC_ENTRY_POINT_H__
