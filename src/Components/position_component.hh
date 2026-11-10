#pragma once

#include "../framework/component.hh"

/// <summary>
/// Example a specific component class that stores the position of an Entity
/// </summary>
class PositionComponent : public Component
{
protected:
    int x;
    int y;
public:
public:
    PositionComponent(int x, int y);
    int getX() const;
    int getY() const;
    void setPosition(int x, int y);
    ~PositionComponent();
};