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

int mode = 0;

Player* player;

InputEventManager* inputManager;

bool ShowFrameworkMenu();

void Level_1_Load()
{
    player = new Player;


    inputManager = new InputEventManager;
}

void Level_1_Init()
{
    //add the components of the player
    RenderComponent* PlayerRender = new RenderComponent();
    player->attach(PlayerRender);
    PositionComponent* PlayerPosition = new PositionComponent(0, -200);
    player->attach(PlayerPosition);
    PlayerComponent* PlayerComp = new PlayerComponent();
    player->attach(PlayerComp);


    inputManager->registerEventHandler(new EventHandler<PlayerComponent, PlayerMoveEvent>(PlayerComp, &PlayerComponent::OnMove));
}

void Level_1_Update()
{
    // core keyboard shortcuts and GUI, do not delete this code!
    KeyboardInput();
    bool guiActive = ShowFrameworkMenu();


}

void Level_1_Render()
{
    // clear frame buffer, do not delete this code
    AEGfxSetClearColor(AEGfxColor(0, 0, 0));
    AEGfxClearBuffer();

    RenderComponent* PlayerRender = static_cast<RenderComponent*>(player->getComponent("Render"));
    PlayerRender->Draw();
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
        event.mDistance = 2;
        inputManager->notifyEvent(&event);
    }
    if (AEInputKeyPressed('A')) {
        PlayerMoveEvent event;
        event.mDistance = -2;
        inputManager->notifyEvent(&event);
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

