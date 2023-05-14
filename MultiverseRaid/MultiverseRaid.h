#ifndef _MULTIVERSE_RAID_H_
#define _MULTIVERSE_RAID_H_

#include "Game.h"
#include "Audio.h"
#include "Scene.h"
#include "Background.h"
#include "Player.h"
#include "Hud.h"
#include "WaveGenerator.h"

enum ObjectIds { PLAYER, PLAYER_PASSIVE, MISSILE, AVATAR, ENEMY, PLAYER_ATTACK, WALLHIT };

enum SoundIds { THEME, START, FIRE, EXPLODE, HITWALL };

class MultiverseRaid : public Game {
    private:
        WaveGenerator* waveGenerator = nullptr;
        Background * backg = nullptr;
        Hud * hud = nullptr;
        bool viewBBox = false;

    public:
        static uint gameWave;
        static uint remainingEnemies;

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