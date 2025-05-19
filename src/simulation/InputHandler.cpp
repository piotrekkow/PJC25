#include "InputHandler.h"
#include <iostream>

InputHandler::InputHandler()
{
    // placeholder
}

void InputHandler::beginFrame()
{
    // placeholder
}

bool InputHandler::isKeyPressed(int key) const
{
    return ::IsKeyPressed(key);
}

bool InputHandler::isKeyDown(int key) const
{
    return ::IsKeyDown(key);
}

bool InputHandler::isKeyReleased(int key) const
{
    return ::IsKeyReleased(key);
}

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