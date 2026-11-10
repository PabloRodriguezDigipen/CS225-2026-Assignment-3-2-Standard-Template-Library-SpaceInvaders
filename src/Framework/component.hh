#pragma once

#include <string.h>
#include <iostream>

class Entity;


/// <summary>
/// Abstract class for all components that can be attached to entities
/// </summary>
class Component
{
protected:
    // Name of the component. All componenet must have an unique Id
    const char* name;
    // Pointer to the Entity that owns thew component. 
	Entity* mOwner;
public:
    
    // Default constructor for the component
    Component(const char* name);
    
    // Gets the name of the component
    const char* getName();
    
    // Get the entity that owns the component
	Entity* getOwner();

    // Set the owne of the component
    void setOwner(Entity* owner);

    // Default destroyer for the abstract class
    virtual ~Component() = default;
};
