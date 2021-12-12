//
//  EntryPoint.h
//  Hazel
//
//  Created by Johan Solbakken on 09/12/2021.
//

#pragma once

#include "hzpch.h"

#include "Application.hpp"

extern Hazel::Application* Hazel::CreateApplication();

int main(int argc, char** argv) {
    Hazel::Log::Init();
    
    auto app = Hazel::CreateApplication();
    app->Run();
    delete app;
}

