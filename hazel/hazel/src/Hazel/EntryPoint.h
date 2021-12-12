//
//  EntryPoint.h
//  Hazel
//
//  Created by Johan Solbakken on 09/12/2021.
//

#pragma once

#include "Application.hpp"

#include <iostream>

extern Hazel::Application* Hazel::CreateApplication();

int main(int argc, char** argv) {
    Hazel::Log::Init();
    HZ_CORE_WARN("Initialized log");
    HZ_CLIENT_INFO("Hello");
    
    auto app = Hazel::CreateApplication();
    app->Run();
    delete app;
}

