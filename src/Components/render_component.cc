#pragma once

#include "AECore/inc/AEEngine.h"
#include "../Framework/entity.hh"

#include "render_component.hh"
#include "position_component.hh"

RenderComponent::RenderComponent(int w, int h) : Component("Render")
{
	width = w;
	height = h;
}

void RenderComponent::Draw()
{
	PositionComponent* position = static_cast<PositionComponent*>(mOwner->getComponent("Position"));
	AEGfxRect(position->getX(), position->getY(), 0,  width, height, AEGfxColor(255, 0, 0));
}

RenderComponent::~RenderComponent() {

}