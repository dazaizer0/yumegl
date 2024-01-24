#pragma once

#include "../../config.h"

bool isKeyPressed(char key) {
    if (GetAsyncKeyState(key) & 0x8000) {
        return true;
    }
    else {
        return false;
    }
}

bool isKeyClicked(char key) {
    static bool keyState = false;
    bool currentKeyState = GetAsyncKeyState(key) & 0x8001;

    if (currentKeyState && !keyState) {
        keyState = true;
        return true;
    }
    else if (!currentKeyState) {
        keyState = false;
    }

    return false;
}
