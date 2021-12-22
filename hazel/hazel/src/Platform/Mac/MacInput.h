//
//  MacInput.hpp
//  Hazel
//
//  Created by Johan Solbakken on 13/12/2021.
//

#pragma once

#include "Hazel/Input.h"

namespace Hazel {

class MacInput : public Input {
protected:
    virtual bool IsKeyPressedImpl(int keycode) override;
    virtual bool IsMouseButtonPressedImpl(int button) override;
    virtual float GetMouseXImpl() override;
    virtual float GetMouseYImpl() override;
    virtual std::pair<float, float> GetMousePositionImpl() override;
};

}
