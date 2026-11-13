#pragma once
#include "event.hh"
#include "event_handlers.hh"

//event fot players input
class InputEventManager : public EventManager {
public:
    void update() override {}
};

class EnemyEventManager : public EventManager {
public:
    void update() override {}
};

class ResetEventManager : public EventManager {
public:
    void update() override {}
};

//event to move player
class PlayerMoveEvent : public Event {
public:
    int mDistance = 0;
};

class PlayerHitEvent : public Event {};

class EnemyDirectionEvent : public Event {};

//event for game reset
class Reset : public Event {};