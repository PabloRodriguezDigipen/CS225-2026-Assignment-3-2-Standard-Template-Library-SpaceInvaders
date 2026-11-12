#pragma once
#include "entity.hh"
#include "../Components/game_components.hh"

class Player : public Entity {
	void Update() override;
	void Draw() override;
};

class Bullet : public Entity {
public:
	void Update() override;
	void Draw() override;
};
