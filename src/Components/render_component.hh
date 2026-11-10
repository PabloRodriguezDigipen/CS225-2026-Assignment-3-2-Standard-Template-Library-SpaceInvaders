#pragma once

#include "../Framework/component.hh"

/// <summary>
/// Exampe of a Render component class that draw an Entity
/// </summary>
class RenderComponent : public Component
{
public:
    RenderComponent();
    
    virtual void Draw();
    
    ~RenderComponent();
};
