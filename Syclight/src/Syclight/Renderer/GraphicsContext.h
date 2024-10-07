#pragma once

#include "Syclight/Common.h"

namespace syc
{
	class GraphicsContext
	{
	public:
		virtual void_ Init() = 0;
		virtual void_ SwapBuffers() = 0;
	};
}