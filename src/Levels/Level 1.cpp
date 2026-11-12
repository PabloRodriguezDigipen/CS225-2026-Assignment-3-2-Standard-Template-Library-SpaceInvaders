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

int mode = 0;

Player* player;
std::vector<Bullet*> playerBullets;

InputEventManager* inputManager;

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

    inputManager = new InputEventManager;
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

    inputManager->registerEventHandler(new EventHandler<PlayerComponent, PlayerMoveEvent>(PlayerComp, &PlayerComponent::OnMove));
    inputManager->registerEventHandler(new EventHandler<PlayerComponent, Reset>(PlayerComp, &PlayerComponent::OnReset));


    for_each(playerBullets.begin(), playerBullets.end(), [](Bullet* current)
        {
            RenderComponent* BulletRender = new RenderComponent(10, 20);
            current->attach(BulletRender);
            PositionComponent* BulletPosition = new PositionComponent(0, -500);
            current->attach(BulletPosition);
            BulletComponent* BulletComp = new BulletComponent(false);
            current->attach(BulletComp);

            inputManager->registerEventHandler(new EventHandler<BulletComponent, Reset>(BulletComp, &BulletComponent::OnReset));
        });
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

