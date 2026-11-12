#pragma once
#include "../Framework/component.hh"
#include "../Framework/game_events.hh"
#include "position_component.hh"
#include "../Framework/entity.hh"

//player
class PlayerComponent : public Component {
protected:
public:
    //default constructor
    PlayerComponent();
    //functions to handle events
    void OnMove(PlayerMoveEvent* event);
    void OnHit(PlayerHitEvent* event);
    void OnReset(Reset* event);
};

class BulletComponent : public Component {
protected:
    bool enemy = false;
    int speed = 10;

public:
    //default constructor
    BulletComponent(bool isEnemy);

    bool IsEnemy();
    int Speed();

    //functions to handle events
    void OnReset(Reset* event);
};