#pragma once

#include "Syclight/Layer.h"
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

	/*private:
		bool4 OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);
		bool4 OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
		bool4 OnMouseMovedEvent(MouseMovedEvent& e);
		bool4 OnMouseScrolledEvent(MouseScrolledEvent& e);
		bool4 OnKeyPressedEvent(KeyPressedEvent& e);
		bool4 OnKeyReleasedEvent(KeyReleasedEvent& e);
		bool4 OnKeyTypedEvent(KeyTypedEvent& e);
		bool4 OnWindowResizedEvent(WindowResizeEvent& e);*/

	private:
		float m_Time = 0.0f;
	};
}


