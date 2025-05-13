// src/input/InputHandler.cpp
#include "InputHandler.h"
#include <iostream>

InputHandler::InputHandler()
{
    // Initialization if needed in the future
}

void InputHandler::beginFrame()
{
    // This is where you might update states if you were tracking them manually
    // For example, resetting lists of keys pressed/released this specific frame.
    // Raylib's IsKeyPressed/Released already handle this "event" nature.
}

// --- Keyboard Input ---
bool InputHandler::isKeyPressed(int key) const
{
    return ::IsKeyPressed(key); // Use :: to ensure global scope for Raylib functions
}

bool InputHandler::isKeyDown(int key) const
{
    return ::IsKeyDown(key);
}

bool InputHandler::isKeyReleased(int key) const
{
    return ::IsKeyReleased(key);
}

// --- Mouse Input ---
bool InputHandler::isMouseButtonPressed(int button) const
{
    return ::IsMouseButtonPressed(button);
}

bool InputHandler::isMouseButtonDown(int button) const
{
    return ::IsMouseButtonDown(button);
}

bool InputHandler::isMouseButtonReleased(int button) const
{
    return ::IsMouseButtonReleased(button);
}

Vector2 InputHandler::getMousePosition() const
{
    return ::GetMousePosition();
}

Vector2 InputHandler::getMouseDelta() const
{
    return ::GetMouseDelta();
}

float InputHandler::getMouseWheelMove() const
{
    return ::GetMouseWheelMove();
}