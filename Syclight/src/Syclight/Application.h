#pragma once

#ifndef __SYC_APPLICATION_H__

#include "Core.h"

namespace syc
{
	class SYC_API Application
	{
	public:
		Application();
		virtual ~Application();

		void_ Run();
	};

	// 客户端接口API
	Application* CreateApplication();

}

#endif // !__SYC_APPLICATION_H__