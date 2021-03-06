//
//  LayerStack.hpp
//  Hazel
//
//  Created by Johan Solbakken on 13/12/2021.
//

#pragma once

#include "Layer.h"

#include <vector>

namespace Hazel
{
	
	class LayerStack
	{
	public:
		LayerStack();
		~LayerStack();
		
		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		void PopLayer(Layer* layer);
		void PopOverlay(Layer* overlay);
		
		std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
		std::vector<Layer*>::iterator end() { return m_Layers.end(); }
		
	private:
		std::vector<Layer*> m_Layers;
		int32_t m_LayerInsertIndex = 0;
	};
	
}
