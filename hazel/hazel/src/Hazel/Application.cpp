//
//  Application.cpp
//  Hazel
//
//  Created by Johan Solbakken on 09/12/2021.
//

#include "hzpch.h"

#include "Application.hpp"

#include "Log.hpp"
#include "Events/ApplicationEvent.h"

namespace Hazel {

Application::Application() {
    
}

Application::~Application() {
    
}

void Application::Run() {
    WindowResizeEvent e(1028, 420);
    if (e.IsInCategory(EventCategoryApplication)) {
        HZ_TRACE(e);
    } else {
        HZ_CORE_ERROR(e);
    }
    while (true);
}

}
