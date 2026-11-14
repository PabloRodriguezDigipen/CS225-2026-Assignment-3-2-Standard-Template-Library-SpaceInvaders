#pragma once
#include "entity.hh"
#include "game_entities.hh"
#include <AEEngine.h>
#include <algorithm>
#include <functional>

class CollisionManager : public EventManager {
    //pointers to the game elements
    Player* mPlayer;
    std::vector<Bullet*> mPlayerBullets;

    std::vector<Enemy*> mEnemies;
    std::vector<Bullet*> mEnemyBullets;


public:
    //default constructos
    CollisionManager(Player* player, std::vector<Bullet*>& playerBullets, std::vector<Enemy*>& enemies, std::vector<Bullet*>& enemyBullets);
    //update
    void update() override;
};
