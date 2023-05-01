#ifndef _MULTIVERSE_RAID_H_
#define _MULTIVERSE_RAID_H_

#include "Game.h"
#include "Audio.h"
#include "Scene.h"
#include "Background.h"
#include "Player.h"
#include "Hud.h"

enum ObjectIds { PLAYER, MISSILE, BLUE, GREEN, MAGENTA, ORANGE, WALLHIT };

enum SoundIds { THEME, START, FIRE, EXPLODE, HITWALL };

class MultiverseRaid : public Game
{
private:
    Background * backg = nullptr;
    Hud * hud = nullptr;
    bool viewBBox = false;

public:
    static Player * player;
    static Audio * audio;
    static Scene * scene;
    static bool viewHUD;

    void Init();
    void Update();
    void Draw();
    void Finalize();
};

#endif