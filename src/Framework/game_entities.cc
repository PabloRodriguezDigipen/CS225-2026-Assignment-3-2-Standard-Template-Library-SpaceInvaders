#include "game_entities.hh"

void Player::Update() {

}

void Player::Draw() {

}

void Bullet::Update() {
	BulletComponent* bulletComp = static_cast<BulletComponent*>(getComponent("Bullet"));
	PositionComponent* posComp = static_cast<PositionComponent*>(getComponent("Position"));

	if (bulletComp->IsEnemy())
		posComp->setPosition(posComp->getX(), posComp->getY() - bulletComp->Speed());
	else
		posComp->setPosition(posComp->getX(), posComp->getY() + bulletComp->Speed());

	if (posComp->getY() < -300 || posComp->getY() > 300) {
		active = false;
		posComp->setPosition(0, -500);
	}
}

void Bullet::Draw() {

}
