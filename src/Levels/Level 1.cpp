#include <AEEngine.h>
#include <imgui/imgui.h>
#include "Level 1.h"
#include "../Framework/entity.hh"
#include "../Framework/game_entities.hh"
#include "../Framework/event.hh"
#include "../Components/render_component.hh"
#include "../Components/position_component.hh"
#include "../Components/game_components.hh"
#include "../Framework/game_events.hh"
#include <algorithm>
#include <functional>
#include <cstdlib>

int mode = 0;

Player* player;
std::vector<Bullet*> playerBullets;

std::vector<Enemy*> enemies;
std::vector<Bullet*> enemyBullets;

InputEventManager* inputManager;
EnemyEventManager* enemyManager;
ResetEventManager* resetManager;

bool ShowFrameworkMenu();

void Level_1_Load()
{
    player = new Player;
    player->active = true;

    for (int i = 0; i < 10; i++) {
        Bullet* bullet = new Bullet;
        bullet->active = false;
        playerBullets.push_back(bullet);
    }

    for (int i = 0; i < 10; i++) {
        Bullet* bullet = new Bullet;
        bullet->active = false;
        enemyBullets.push_back(bullet);
    }

    for (int i = 0; i < 30; i++) {
        Enemy* enemy = new Enemy;
        enemy->active = false;
        enemies.push_back(enemy);
    }

    inputManager = new InputEventManager;
    enemyManager = new EnemyEventManager;
    resetManager = new ResetEventManager;
}

void Level_1_Init()
{
    //add the components of the player
    RenderComponent* PlayerRender = new RenderComponent(50, 20);
    player->attach(PlayerRender);
    PositionComponent* PlayerPosition = new PositionComponent(0, -200);
    player->attach(PlayerPosition);
    PlayerComponent* PlayerComp = new PlayerComponent();
    player->attach(PlayerComp);

    player->active = true;

    inputManager->registerEventHandler(new EventHandler<PlayerComponent, PlayerMoveEvent>(PlayerComp, &PlayerComponent::OnMove));
    resetManager->registerEventHandler(new EventHandler<PlayerComponent, Reset>(PlayerComp, &PlayerComponent::OnReset));


    for_each(playerBullets.begin(), playerBullets.end(), [](Bullet* current)
        {
            RenderComponent* BulletRender = new RenderComponent(10, 20);
            current->attach(BulletRender);
            PositionComponent* BulletPosition = new PositionComponent(0, -500);
            current->attach(BulletPosition);
            BulletComponent* BulletComp = new BulletComponent(false);
            current->attach(BulletComp);

            resetManager->registerEventHandler(new EventHandler<BulletComponent, Reset>(BulletComp, &BulletComponent::OnReset));
        });

    for_each(enemyBullets.begin(), enemyBullets.end(), [](Bullet* current)
        {
            RenderComponent* BulletRender = new RenderComponent(10, 20);
            current->attach(BulletRender);
            PositionComponent* BulletPosition = new PositionComponent(0, -500);
            current->attach(BulletPosition);
            BulletComponent* BulletComp = new BulletComponent(true);
            current->attach(BulletComp);

            resetManager->registerEventHandler(new EventHandler<BulletComponent, Reset>(BulletComp, &BulletComponent::OnReset));
        });

    for_each(enemies.begin(), enemies.end(), [](Enemy* current)
        {
            RenderComponent* EnemyRender = new RenderComponent(40, 15);
            current->attach(EnemyRender);
            PositionComponent* EnenmyPosition = new PositionComponent(700, 0);
            current->attach(EnenmyPosition);
            EnemyComponent* EnemyComp = new EnemyComponent();
            current->attach(EnemyComp);

            current->active = true;

            resetManager->registerEventHandler(new EventHandler<EnemyComponent, Reset>(EnemyComp, &EnemyComponent::OnReset));
            enemyManager->registerEventHandler(new EventHandler<EnemyComponent, EnemyDirectionEvent>(EnemyComp, &EnemyComponent::OnDirection));
        });

    int enemiesPerRow = 6, count = 0;
    int X = 0, Y = 0;
    for (int i = 0; i < enemies.size(); i++) {
        PositionComponent* position = static_cast<PositionComponent*>(enemies.at(i)->getComponent("Position"));
        position->setPosition(X, Y);
        X += 50;
        count++;
        if (count == enemiesPerRow){
            Y += 40;
            X = 0;
            count = 0;
        }
    }
}

void Level_1_Update()
{
    // core keyboard shortcuts and GUI, do not delete this code!
    KeyboardInput();
    bool guiActive = ShowFrameworkMenu();

    for_each(playerBullets.begin(), playerBullets.end(), [](Bullet* current)
        {
            if (current->active) {
                current->Update();
            }
        });

    for_each(enemyBullets.begin(), enemyBullets.end(), [](Bullet* current)
        {
            if (current->active) {
                current->Update();
            }
        });


    bool changeDirection = false;
    for_each(enemies.begin(), enemies.end(), [&changeDirection](Enemy* current)
        {
            if (current->active) {
                current->Update();

                PositionComponent* posComp = static_cast<PositionComponent*>(current->getComponent("Position"));
                if (posComp->getX() < -350 || posComp->getX() > 350) {
                    changeDirection = true;
                }
                int shoot = rand();

                if (shoot < 18) {
                    AEVec2 bulletPos = AEVec2(posComp->getX(), posComp->getY() - 20);

                    bool found = false;
                    for_each(enemyBullets.begin(), enemyBullets.end(), [&found, &bulletPos](Bullet* current)
                        {
                            if (!found && !current->active) {
                                PositionComponent* bulletPosition = static_cast<PositionComponent*>(current->getComponent("Position"));
                                bulletPosition->setPosition(bulletPos.x, bulletPos.y);
                                current->active = true;

                                found = true;
                            }
                        });
                }
            }
        });

    if (changeDirection) {
        EnemyDirectionEvent event;
        enemyManager->notifyEvent(&event);
    }
}

void Level_1_Render()
{
    // clear frame buffer, do not delete this code
    AEGfxSetClearColor(AEGfxColor(0, 0, 0));
    AEGfxClearBuffer();

    RenderComponent* PlayerRender = static_cast<RenderComponent*>(player->getComponent("Render"));
    PlayerRender->Draw();

    for_each(playerBullets.begin(), playerBullets.end(), [](Bullet* current)
        {
            if (current->active) {
                RenderComponent* render = static_cast<RenderComponent*>(current->getComponent("Render"));
                render->Draw();
            }
        });

    for_each(enemyBullets.begin(), enemyBullets.end(), [](Bullet* current)
        {
            if (current->active) {
                RenderComponent* render = static_cast<RenderComponent*>(current->getComponent("Render"));
                render->Draw();
            }
        });

    for_each(enemies.begin(), enemies.end(), [](Enemy* current)
        {
            if (current->active) {
                RenderComponent* render = static_cast<RenderComponent*>(current->getComponent("Render"));
                render->Draw();
            }
        });
}

void Level_1_Free()
{

}

void Level_1_Unload()
{
}

void KeyboardInput()
{//move the player when pressing W or S
    if (AEInputKeyPressed('D')) {
        PlayerMoveEvent event;
        event.mDistance = 4;
        inputManager->notifyEvent(&event);
    }
    if (AEInputKeyPressed('A')) {
        PlayerMoveEvent event;
        event.mDistance = -4;
        inputManager->notifyEvent(&event);
    }
    if (AEInputKeyTriggered(32)) {
        PositionComponent* playerPosition = static_cast<PositionComponent*>(player->getComponent("Position"));
        AEVec2 bulletPos = AEVec2(playerPosition->getX(), playerPosition->getY() + 20);

        bool found = false;
        for_each(playerBullets.begin(), playerBullets.end(), [&found, &bulletPos](Bullet* current)
            {
                if (!found && !current->active) {
                    PositionComponent* bulletPosition = static_cast<PositionComponent*>(current->getComponent("Position"));
                    bulletPosition->setPosition(bulletPos.x, bulletPos.y);
                    current->active = true;

                    found = true;
                }
            });
    }
    if (AEInputKeyTriggered('R'))
        AESetGameStateNext(AE_GS_RESTART);
    if (AEInputKeyTriggered('Q') && AEInputKeyPressed(AE_KEY_CTRL))
        AESetGameStateNext(AE_GS_QUIT);
}

bool ShowFrameworkMenu()
{
    bool isGuiActive = false;
    mode = 0;

    // show File options 
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("Mode")) {

            if (ImGui::MenuItem("Restart", "1"))
                mode = 1;

            ImGui::EndMenu();
        }

        auto mSize = ImGui::GetWindowHeight();
        AEVec2 mouseVP = AEGetMouseData().position + AEVec2((float)AEGetSysWindowWidth() / 2.0f, (float)AEGetSysWindowHeight() / 2.0f);
        auto inMenu = mouseVP.y >= (AEGetSysWindowHeight() - mSize);
        isGuiActive = ImGui::IsAnyItemActive() || ImGui::IsAnyItemHovered() || inMenu;

        ImGui::EndMainMenuBar();
    }

    if (mode == 1) {
        AESetGameStateNext(AE_GS_RESTART);
    }

    return isGuiActive;
}

