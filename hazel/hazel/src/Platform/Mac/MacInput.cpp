//
//  MacInput.cpp
//  Hazel
//
//  Created by Johan Solbakken on 13/12/2021.
//

#include "hzpch.h"
#include "MacInput.hpp"

#include "Hazel/Application.hpp"
#include <GLFW/glfw3.h>

namespace Hazel {

Input* Input::s_Instance = new MacInput();

bool MacInput::IsKeyPressedImpl(int keycode)
{
    auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
    auto state = glfwGetKey(window, keycode);
    return state == GLFW_PRESS || state == GLFW_REPEAT;
}

bool MacInput::IsMouseButtonPressedImpl(int button) {
    auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
    auto state = glfwGetMouseButton(window, button);
    return state == GLFW_PRESS;
}

float MacInput::GetMouseXImpl() {
    auto[x, y] = GetMousePositionImpl();
    return x;
}

float MacInput::GetMouseYImpl()  {
    auto[x, y] = GetMousePositionImpl();
    return y;
}

std::pair<float, float> MacInput::GetMousePositionImpl() {
    auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
    return {(float)xpos,(float) ypos};
}

}
