#pragma once

#include "Syclight/Core/Layer.h"
#include <Syclight/Events/ApplicationEvent.h>
#include <Syclight/Events/MouseEvent.h>
#include <Syclight/Events/KeyEvent.h>

namespace syc
{
	class SYC_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void_ OnAttach() override;
		virtual void_ OnDetach() override;
		virtual void_ OnImGuiRender() override;
		//virtual void_ OnUpdate() override;
		//virtual void_ OnEvent(Event& event);

		void_ Begin();
		void_ End();

	private:
		float m_Time = 0.0f;
	};
}


