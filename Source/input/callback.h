#pragma once

#include <iostream>
#include <functional>
#include <map>

#include <GLFW/glfw3.h>

#include "input.h"
#include "../camera/camera.h"


class PlayerCallback final {
private:
    input::Token mInputToken;

public:
    PlayerCallback();
    ~PlayerCallback();

    void update(float delta_time);
};



