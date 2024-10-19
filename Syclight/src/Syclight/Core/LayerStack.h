#pragma once

#include "Syclight/Core/Core.h"
#include "Syclight/Core/Layer.h"

#include <vector>

namespace syc
{
	class SYC_API LayerStack
	{
	private:
		std::vector<Layer*> m_Layers;
		/*std::vector<Layer*>::iterator m_LayerInsert;*/
		uint32 m_LayerInsertIndex = 0;

	public:
		LayerStack();
		~LayerStack();

		void_ PushLayer(Layer* layer);
		void_ PushOverlay(Layer* overlay);
		void_ PopLayer(Layer* layer);
		void_ PopOverlay(Layer* overlay);

		std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
		std::vector<Layer*>::iterator end() { return m_Layers.end(); }
	};
}