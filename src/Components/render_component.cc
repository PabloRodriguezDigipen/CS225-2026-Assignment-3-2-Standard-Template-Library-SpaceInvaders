#pragma once

#include "AECore/inc/AEEngine.h"
#include "../Framework/entity.hh"

#include "render_component.hh"
#include "position_component.hh"

RenderComponent::RenderComponent() : Component("Render")
{

}

void RenderComponent::Draw()
{
	PositionComponent* position = static_cast<PositionComponent*>(mOwner->getComponent("Position"));
	AEGfxCircle(position->getX(), position->getX(), 50, AEGfxColor(255, 0, 0), 20);
}

RenderComponent::~RenderComponent() {

}