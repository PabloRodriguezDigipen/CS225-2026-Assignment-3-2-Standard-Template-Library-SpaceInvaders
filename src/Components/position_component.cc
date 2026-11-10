#include "position_component.hh"

PositionComponent::PositionComponent(int x, int y) :Component("Position")
{
    this->x = x;
    this->y = y;
}

int PositionComponent::getX() const
{
    return x;
}

int PositionComponent::getY() const
{
    return y;
}

void PositionComponent::setPosition(int x, int y) {
    this->x = x;
    this->y = y;
}

PositionComponent::~PositionComponent() {

}