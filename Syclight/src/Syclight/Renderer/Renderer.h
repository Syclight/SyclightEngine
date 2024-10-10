#pragma once

namespace syc
{
	enum class SYC_API RendererAPI
	{
		None = 0,
		OpenGL = 1
	};

	class SYC_API Renderer
	{
	public:
		inline static RendererAPI GetAPI() { return s_RendererAPI; }

	private:
		static RendererAPI s_RendererAPI;
	};

	
}


