//
//  EntryPoint.h
//  Hazel
//
//  Created by Johan Solbakken on 09/12/2021.
//

#pragma once

#include "Application.hpp"

#include "spdlog/spdlog.h"

#include <iostream>

extern Hazel::Application* Hazel::CreateApplication();

int main(int argc, char** argv) {
    auto app = Hazel::CreateApplication();
    app->Run();
    delete app;
}

