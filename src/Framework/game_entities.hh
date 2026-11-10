#pragma once
#include "entity.hh"

class Player : public Entity {
	void Update() override;
	void Draw() override;
};
