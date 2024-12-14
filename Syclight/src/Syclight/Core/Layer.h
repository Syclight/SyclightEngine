#pragma once

#include "Syclight/Core/Core.h"
#include "Syclight/Events/Event.h"
#include "Syclight/Core/Timestep.h"

namespace syc
{
	/*
	* interface:
	** virtual void_ OnAttach()
	** virtual void_ OnDetach()
	** virtual void_ OnUpdate(syc::Timestep& timestep)
	** virtual void_ OnImGuiRender() default
	** virtual void_ OnEvent(syc::Event& event)
	*/
	class SYC_API Layer
	{
	protected:
		std::string m_DebugName;

	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer() = default;

		virtual void_ OnAttach() {}
		virtual void_ OnDetach() {}
		virtual void_ OnUpdate(Timestep timestep) {}
		virtual void_ OnImGuiRender() {}
		virtual void_ OnEvent(Event& event) {}

		inline const std::string& GetName() const { return m_DebugName; }
	};
}

