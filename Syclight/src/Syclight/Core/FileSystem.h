#pragma once

#include "Syclight/Core/Buffer.h"

namespace syc {

	class FileSystem
	{
	public:
		// TODO: move to FileSystem class
		static Buffer ReadFileBinary(const std::filesystem::path& filepath);
	};

}