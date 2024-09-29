#pragma once

#include "Syclight/Layer.h"

namespace syc
{
	class SYC_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void_ OnAttach();
		void_ OnDetach();
		void_ OnUpdate();
		void_ OnEvent();

	private:
		float m_Time = 0.0f;
	};
}


