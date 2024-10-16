#pragma once

#include "Syclight/Core.h"
#include <string>

namespace syc
{
	class SYC_API Texture
	{
	public:
		virtual ~Texture() = default;

		virtual uint32 GetWidth() const = 0;
		virtual uint32 GetHeight() const = 0;

		virtual void_ Bind(uint32 slot = 0) const = 0;
	};

	class SYC_API Texture2D : public Texture
	{
	public:
		static Ref<Texture2D> Create(const std::string& path);
	};
}


