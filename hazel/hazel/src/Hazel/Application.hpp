//
//  Application.hpp
//  Hazel
//
//  Created by Johan Solbakken on 09/12/2021.
//

#pragma once

namespace Hazel {

class Application {
public:
    Application();
    virtual ~Application();
    void Run();
};

// To be defined in client
Application* CreateApplication();

}
