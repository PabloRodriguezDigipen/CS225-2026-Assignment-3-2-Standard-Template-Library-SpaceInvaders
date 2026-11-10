#include "game_components.hh"

PlayerComponent::PlayerComponent() : Component("Player") {}

void PlayerComponent::OnMove(PlayerMoveEvent* event) {
	//get the position component
	PositionComponent* position = static_cast<PositionComponent*>(mOwner->getComponent("Position"));

	//change the position
	position->setPosition(position->getX() + event->mDistance, position->getY());

	//dont surpass the limits
	if (position->getX() > 250)
		position->setPosition(250, position->getY());
	else if (position->getX() < -250)
		position->setPosition(-250, position->getY());
}

void PlayerComponent::OnHit(PlayerHitEvent* event) {

}

void PlayerComponent::OnReset(Reset* event) {

}
