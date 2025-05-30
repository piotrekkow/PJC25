#pragma once

#include <raylib.h>
#include <set>  // Keys are unique unlike in vector

class InputHandler
{
public:
    InputHandler();

    void beginFrame();

    // --- Keyboard ---
    bool isKeyPressed(int key) const;
    bool isKeyDown(int key) const;
    bool isKeyReleased(int key) const;

    // --- Mouse ---
    bool isMouseButtonPressed(int button) const;
    bool isMouseButtonDown(int button) const;
    bool isMouseButtonReleased(int button) const;
    Vector2 getMousePosition() const;
    Vector2 getMouseDelta() const;
    float getMouseWheelMove() const;
};