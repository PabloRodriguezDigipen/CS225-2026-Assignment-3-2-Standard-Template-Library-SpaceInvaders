#include "game_components.hh"

PlayerComponent::PlayerComponent() : Component("Player") {}

void PlayerComponent::OnMove(PlayerMoveEvent* event) {
	//get the position component
	PositionComponent* position = static_cast<PositionComponent*>(mOwner->getComponent("Position"));

	//change the position
	position->setPosition(position->getX() + event->mDistance, position->getY());

	//dont surpass the limits
	if (position->getX() > 350)
		position->setPosition(350, position->getY());
	else if (position->getX() < -350)
		position->setPosition(-350, position->getY());
}

void PlayerComponent::OnHit(PlayerHitEvent* event) {

}

void PlayerComponent::OnReset(Reset* event) {

}

BulletComponent::BulletComponent(bool isEnemy) : Component("Bullet") {
	enemy = isEnemy;
}

bool BulletComponent::IsEnemy() {
	return enemy;
}

int BulletComponent::Speed() {
	return speed;
}

void BulletComponent::OnReset(Reset* event) {

}
