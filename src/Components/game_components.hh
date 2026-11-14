#pragma once
#include "../Framework/component.hh"
#include "../Framework/game_events.hh"
#include "position_component.hh"
#include "../Framework/entity.hh"

//component to check collisions
class CollisionComponent : public Component {
protected:
    //data for collision (position will be taken from its own component)
    int mWidth;
    int mHeight;
public:
    //default constructor
    CollisionComponent(int width, int height);
    //getters
    int getWidth() const;
    int getHeight() const;
    //default destructor
    ~CollisionComponent() = default;
};

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
    int speed = 5;

public:
    //default constructor
    BulletComponent(bool isEnemy);

    bool IsEnemy();
    int Speed();

    //functions to handle events
    void OnReset(Reset* event);
};

//enemy
class EnemyComponent : public Component {
protected:
    bool toRight = true;
    int speed = 1;

public:
    //default constructor
    EnemyComponent();

    bool Right();
    int Speed();

    //functions to handle events
    void OnDirection(EnemyDirectionEvent* event);
    void OnReset(Reset* event);
};