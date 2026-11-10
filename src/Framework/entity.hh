#pragma once
#include <vector>
#include "component.hh"

/// <summary>
/// Abstract class for all Entities
/// </summary>
class Entity
{
protected:
    // Components attached to the class
    std::vector<Component*> components;
public:
    // Get a component by their name
    Component* getComponent(const char* name);
    
    // Attach a component to the Entity
    void attach(Component* component);
    
    // Update method for the entity, must be overriden and called from the game state Update method
    virtual void Update() = 0;

    // Draw method for the entity, must be overriden and called from the game state Draw method
    virtual void Draw() = 0;

    // Default destroyer for the class
    virtual ~Entity();
};

