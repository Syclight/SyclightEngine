#pragma once

#ifndef __SYC_ENTRY_POINT_H__
#define __SYC_ENTRY_POINT_H__

extern syc::Application* syc::CreateApplication();

int main(int argc, char** argv)
{
	printf("Syclight Engine Start");
	auto app = syc::CreateApplication();
	app->Run();
	delete app;
	return 0;
}

#endif // !__SYC_ENTRY_POINT_H__
