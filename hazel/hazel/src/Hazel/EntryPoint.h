//
//  EntryPoint.h
//  Hazel
//
//  Created by Johan Solbakken on 09/12/2021.
//

#pragma once

#include "hzpch.h"
#include "Application.h"

// Function to be defined by client
extern Hazel::Application* Hazel::CreateApplication();

// Entry point for application
int main(int argc, char** argv) {
    Hazel::Log::Init();
    
    auto app = Hazel::CreateApplication();
    app->Run();
    delete app;
}

