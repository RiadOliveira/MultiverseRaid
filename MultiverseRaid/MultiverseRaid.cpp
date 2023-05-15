#include "Resources.h"
#include "MultiverseRaid.h"
#include "Engine.h"    
#include "RobotEnemy.h"
#include "WizardEnemy.h"
#include "AlienEnemy.h"
#include "Delay.h"
#include "WizardAvatar.h"
#include "WaveHighlight.h"

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

        audio->Add(THUNDER_STORM_LIGHTING, "Resources/Wizard/ThunderStormLighting.wav");
        audio->Add(FIRE_BALL, "Resources/Wizard/FireBall.wav");
        audio->Add(LASER_BEAM, "Resources/Robot/LaserBeam.wav");
        audio->Add(BLACK_HOLE, "Resources/Alien/BlackHole.wav");
        audio->Add(COSMIC_ORB, "Resources/Alien/CosmicOrb.wav", 3);
        audio->Add(DRONE_ATTACK, "Resources/Robot/DroneAttack.wav", 3);

        audio->Volume(THUNDER_STORM_LIGHTING, 0.05f);
        audio->Frequency(THUNDER_STORM_LIGHTING, 1.5f);
        audio->Volume(FIRE_BALL, 0.05f);
        audio->Frequency(FIRE_BALL, 2.0f);
        audio->Volume(LASER_BEAM, 0.1f);
        audio->Volume(BLACK_HOLE, 0.1f);
        audio->Frequency(BLACK_HOLE, 1.5f);
        audio->Volume(COSMIC_ORB, 0.05f);
        audio->Frequency(COSMIC_ORB, 1.5f);
        audio->Volume(DRONE_ATTACK, 0.01f);

        audio->Add(ALIEN_THEME, "Resources/Alien/AlienTheme.wav");
        audio->Add(WIZARD_THEME, "Resources/Wizard/WizardTheme.wav");
        audio->Add(WIZARD_LEGENDARY_THEME, "Resources/Wizard/WizardLegendaryTheme.wav");
        audio->Add(ROBOT_THEME, "Resources/Robot/RobotTheme.wav");
        
        audio->Volume(ALIEN_THEME, 0.03f);
        audio->Volume(WIZARD_THEME, 0.3f);
        audio->Volume(WIZARD_LEGENDARY_THEME, 0.1f);
        audio->Volume(ROBOT_THEME, 0.04f);

        audio->Add(WIZARD_ENEMY_ATTACK, "Resources/Wizard/WizardEnemyAttack.wav", 5);
        audio->Add(WIZARD_ENEMY_CAST, "Resources/Wizard/WizardEnemyCast.wav", 10);
        audio->Add(ROBOT_ENEMY_ATTACK, "Resources/Robot/RobotEnemyAttack.wav", 5);
        audio->Add(ALIEN_ENEMY_ATTACK, "Resources/Alien/AlienEnemyAttack.wav", 3);

        audio->Volume(WIZARD_ENEMY_ATTACK, 0.02f);
        audio->Volume(WIZARD_ENEMY_CAST, 0.05f);
        audio->Volume(ROBOT_ENEMY_ATTACK, 0.02f);
        audio->Frequency(ROBOT_ENEMY_ATTACK, 2.0f);
        audio->Volume(ALIEN_ENEMY_ATTACK, 0.04f);
    }

    backg   = new Background("Resources/Space.jpg");
    scene   = new Scene();

    waveGenerator = new WaveGenerator();
    player  = new Player();
    hud = new Hud();

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

        if(gameWave > 1) {
            player->LevelUp();
            scene->Add(new WaveHighlight(), STATIC);
        }
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
    Color backgroundColor = WizardAvatar::timeIsStopped ?
        Color(0.4f, 1.0f, 0.4f, 1.0f) : Color(1.0f, 1.0f, 1.0f, 1.0f);

    backg->Draw(viewport, backgroundColor);
    scene->Draw();

    if (viewHUD) hud->Draw();
    if (viewBBox) scene->DrawBBox();
}

void MultiverseRaid::Finalize() {
    scene->Remove(player, STATIC);

    //delete audio;
    delete hud;
    delete scene;
    delete player;
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
