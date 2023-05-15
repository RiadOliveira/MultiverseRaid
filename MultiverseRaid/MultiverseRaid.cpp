#include "Resources.h"
#include "MultiverseRaid.h"
#include "Engine.h"    
#include "RobotEnemy.h"
#include "WizardEnemy.h"
#include "AlienEnemy.h"
#include "Delay.h"

Player * MultiverseRaid::player  = nullptr;
Audio  * MultiverseRaid::audio   = nullptr;
Scene  * MultiverseRaid::scene   = nullptr;
uint     MultiverseRaid::gameWave = 0;
uint     MultiverseRaid::remainingEnemies = 0;
bool     MultiverseRaid::viewHUD = false;

void MultiverseRaid::Init() {
    Size(3840, 2160);
    if(audio == nullptr) {
        audio = new Audio();
        audio->Add(THUNDER_STORM_PHRASE, "Resources/Wizard/ThunderStormPhrase.wav");
        audio->Add(FIRE_BALL, "Resources/Wizard/FireBall.wav");
        audio->Add(THEME, "Resources/Theme.wav");
        audio->Add(FIRE, "Resources/Fire.wav");
        audio->Add(HITWALL, "Resources/Hitwall.wav");
        audio->Add(EXPLODE, "Resources/Explode.wav");
        audio->Add(START, "Resources/Start.wav");

        audio->Volume(THUNDER_STORM_PHRASE, 0.2f);
        audio->Frequency(THUNDER_STORM_PHRASE, 1.5f);

        audio->Volume(FIRE_BALL, 0.2f);
        audio->Frequency(FIRE_BALL, 2.0f);

        audio->Volume(THEME, 0.0f);
        audio->Volume(FIRE, 0.0f);
        audio->Volume(START, 0.0f);
    }

    backg   = new Background("Resources/Space.jpg");
    scene   = new Scene();
    player  = new Player();

    hud = new Hud();
    waveGenerator = new WaveGenerator();

    scene->Add(player, STATIC);
    scene->Add(new Delay(), STATIC);

    float difx = (game->Width() - window->Width()) / 2.0f;
    float dify = (game->Height() - window->Height()) / 2.0f;

    viewport.left = 0.0f + difx;
    viewport.right = viewport.left + window->Width();
    viewport.top = 0.0f + dify;
    viewport.bottom = viewport.top + window->Height();
}

void MultiverseRaid::Update() {
    if (window->KeyDown(VK_ESCAPE)) window->Close();

    if(gameWave > 0 && player->IsDead()) {
        Engine::Next<MultiverseRaid>();
        return;
    }

    if(waveGenerator->FinishedCurrentWave()) {
        waveGenerator->Start(++gameWave);
        if(gameWave > 1) player->LevelUp();
    }

    waveGenerator->UpdateGeneration();
    scene->Update();
    scene->CollisionDetection();

    if (window->KeyPress('B')) viewBBox = !viewBBox;
    if (window->KeyPress('H')) viewHUD = !viewHUD;

    viewport.left   = player->X() - window->CenterX();
    viewport.right  = player->X() + window->CenterX();
    viewport.top    = player->Y() - window->CenterY();
    viewport.bottom = player->Y() + window->CenterY();
            
    if (viewport.left < 0)
    {
        viewport.left  = 0;
        viewport.right = window->Width();
    }
    else if (viewport.right > game->Width())
    {  
        viewport.left  = game->Width() - window->Width();
        viewport.right = game->Width();
    }
                  
    if (viewport.top < 0)
    {
        viewport.top  = 0;
        viewport.bottom = window->Height();
    }
    else if (viewport.bottom > game->Height())
    {
        viewport.top = game->Height() - window->Height();
        viewport.bottom = game->Height();
    }
} 

void MultiverseRaid::Draw() {
    backg->Draw(viewport);
    scene->Draw();

    if (viewHUD) hud->Draw();
    if (viewBBox) scene->DrawBBox();
}

void MultiverseRaid::Finalize() {
    //delete audio;
    delete hud;
    delete scene;
    delete backg;
    delete waveGenerator;

    player = nullptr;
    gameWave = 0;
    remainingEnemies = 0;
}

int APIENTRY WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, 
                     _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
    Engine * engine = new Engine();

    engine->window->Mode(BORDERLESS);
    engine->window->Color(0, 0, 0);
    engine->window->Title("MultiverseRaid");
    engine->window->Icon(IDI_ICON);
    engine->window->Cursor(IDC_CURSOR);
    engine->window->HideCursor(true);
    //engine->graphics->VSync(true);

    int status = engine->Start(
        new MultiverseRaid()
    );

    delete engine;
    return status;
}
