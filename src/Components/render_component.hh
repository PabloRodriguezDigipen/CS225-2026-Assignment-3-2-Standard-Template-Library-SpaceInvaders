#pragma once

#include "../Framework/component.hh"

/// <summary>
/// Exampe of a Render component class that draw an Entity
/// </summary>
class RenderComponent : public Component
{
    int width = 0, height = 0;
public:
    RenderComponent(int w, int h);
    
    virtual void Draw();
    
    ~RenderComponent();
};
