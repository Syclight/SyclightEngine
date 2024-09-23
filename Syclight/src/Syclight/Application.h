#pragma once

#ifndef __SYC_APPLICATION_H__

#include "Common.h"
#include "Core.h"
#include "../Events/Event.h"

namespace syc
{
	class SYC_API Application
	{
	public:
		Application();
		~Application();

		void_ Start();
		void_ Run();
	};

	// 客户端API
	Application* CreateApplication();

}

#endif // !__SYC_APPLICATION_H__