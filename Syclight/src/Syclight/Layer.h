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

	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer() = default;

		virtual void_ OnAttach() {}
		virtual void_ OnDetach() {}
		virtual void_ OnUpdate() {}
		virtual void_ OnImGuiRender() {}
		virtual void_ OnEvent(Event& event) {}

		inline const std::string& GetName() const { return m_DebugName; }
	};
}

