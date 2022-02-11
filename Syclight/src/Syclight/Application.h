#pragma once

#ifndef __SYC_APPLICATION_H__

#include "Common.h"
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

	// ¿Í»§¶ËAPI
	Application* CreateApplication();

}

#endif // !__SYC_APPLICATION_H__