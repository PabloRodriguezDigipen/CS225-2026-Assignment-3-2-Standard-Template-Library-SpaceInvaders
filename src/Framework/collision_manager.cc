#include "collision_manager.hh"

CollisionManager::CollisionManager(Player* player, std::vector<Bullet*>& playerBullets, std::vector<Enemy*>& enemies, std::vector<Bullet*>& enemyBullets) {
	mPlayer = player;
	mPlayerBullets = playerBullets;
	mEnemies = enemies;
	mEnemyBullets = enemyBullets;
}

void CollisionManager::update() {
    //get the player data
    PositionComponent* playerPos = static_cast<PositionComponent*>(mPlayer->getComponent("Position"));
    CollisionComponent* playerCol = static_cast<CollisionComponent*>(mPlayer->getComponent("Collision"));

    for_each(mEnemyBullets.begin(), mEnemyBullets.end(), [&](Bullet* current)
        {
            if (current->active) {
                PositionComponent* bulletPos = static_cast<PositionComponent*>(current->getComponent("Position"));
                AEVec2 bulletPosition = AEVec2(bulletPos->getX(), bulletPos->getY());
                AEVec2 playerPosition = AEVec2(playerPos->getX(), playerPos->getY());
                if (AEStaticPointToStaticRect(&bulletPosition, &playerPosition, playerCol->getWidth(), playerCol->getHeight())) {
                    Reset event;
                    notifyEvent(&event);
                }
            }
        });

    for_each(mPlayerBullets.begin(), mPlayerBullets.end(), [&](Bullet* currentBullet)
        {
            if (currentBullet->active) {
                PositionComponent* bulletPos = static_cast<PositionComponent*>(currentBullet->getComponent("Position"));
                for_each(mEnemies.begin(), mEnemies.end(), [&](Enemy* currentEnemy)
                    {
                        if (currentEnemy->active) {
                            //get the enemy data
                            PositionComponent* EnemyPos = static_cast<PositionComponent*>(currentEnemy->getComponent("Position"));
                            CollisionComponent* EnemyCol = static_cast<CollisionComponent*>(currentEnemy->getComponent("Collision"));
                            AEVec2 bulletPosition = AEVec2(bulletPos->getX(), bulletPos->getY());
                            AEVec2 enemyPosition = AEVec2(EnemyPos->getX(), EnemyPos->getY());
                            if (AEStaticPointToStaticRect(&bulletPosition, &enemyPosition, EnemyCol->getWidth(), EnemyCol->getHeight())) {
                                currentEnemy->active = false;
                                currentBullet->active = false;

                                EnemyPos->setPosition(700, 0);
                                bulletPos->setPosition(0, -500);
                            }
                        }
                    });
            }
        });
}
