#pragma once

#include "Syclight/Core.h"
#include "Syclight/Common.h"
#include "Syclight/Events/Event.h"

namespace syc
{
	class SYC_API Layer
	{
	protected:
		std::string m_DebugName;
		bool4 m_IsAttached = false;

	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer() = default;

		virtual void_ OnAttach() { SetAttached(); }
		virtual void_ OnDetach() { SetDetached(); }
		virtual void_ OnUpdate() {}
		virtual void_ OnImGuiRender() {}
		virtual void_ OnEvent(Event& event) {}

		inline void_ SetAttached() { m_IsAttached = true; }
		inline void_ SetDetached() { m_IsAttached = false; }
		inline const bool4 IsAttached() const { return m_IsAttached; }
		inline const std::string& GetName() const { return m_DebugName; }
	};
}

