#pragma once

#include "Syclight/Core/Core.h"

#include <random>

namespace syc
{
	class SYC_API Random
	{
	public:
		static void_ Init()
		{
			s_RandomEngine.seed(std::random_device()());
		}

		static float32 Float()
		{
			return (float32)s_Distribution(s_RandomEngine) / (float32)std::numeric_limits<uint32>::max();
		}

	private:
		static std::mt19937 s_RandomEngine;
		static std::uniform_int_distribution<std::mt19937::result_type> s_Distribution;
	};
}
