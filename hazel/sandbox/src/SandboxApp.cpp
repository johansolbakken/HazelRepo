//
//  SandboxApp.cpp
//  Sandbox
//
//  Created by Johan Solbakken on 09/12/2021.
//

#include <Hazel.h>

class Sandbox : public Hazel::Application {
public:
    Sandbox() {
        
    }
    
    ~Sandbox() {
        
    }
};

Hazel::Application* Hazel::CreateApplication() {
    return new Sandbox();
}
