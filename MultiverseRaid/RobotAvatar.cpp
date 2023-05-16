#include "RobotAvatar.h"
#include "RobotAttack.h"
#include "MultiverseRaid.h"

RobotAvatar::RobotAvatar() {
    avatarType = ROBOT;
    basicAttackCooldown = 2.5f;

    tileSet = new TileSet(
        "Resources/Robot/RobotAvatar.png",
        250, 300, 4, 8
    );
    animation = new Animation(tileSet, 0.25f, true);

    uint rightSequence[4] = { 0, 1, 2, 3 };
    animation->Add(RIGHT, rightSequence, 4);

    uint leftSequence[4] = { 7, 6, 5, 4 };
    animation->Add(LEFT, leftSequence, 4);
}

RobotAvatar::~RobotAvatar() {
    MultiverseRaid::audio->Stop(ROBOT_THEME);
    MultiverseRaid::audio->Stop(LASER_BEAM);
}

void RobotAvatar::HandleSelectAvatar() {
    drone = new RobotDrone();
    MultiverseRaid::scene->Add(drone, STATIC);
    MultiverseRaid::audio->Play(ROBOT_THEME, true);
}

void RobotAvatar::HandleUnselectAvatar() {
    MultiverseRaid::scene->Delete(drone, STATIC);
    MultiverseRaid::audio->Stop(ROBOT_THEME);
}

void RobotAvatar::HandleBasicAttack(Object* obj) {
    Player* player = MultiverseRaid::player;
    Point* playerPoint = new Point(player->X(), player->Y());

    float angle = Line::Angle(*playerPoint, Point(obj->X(), obj->Y()));
    int laserQuantity = min(max(1,(MultiverseRaid::gameWave - 1) / 3 * 2), 4);

    int angleModifier = 360 / laserQuantity;
    for(int ind=0 ; ind<laserQuantity ; ind++) {
         RobotAttack* attack = new RobotAttack(
            8.0f, playerPoint, angle + angleModifier * ind
        );
        
        MultiverseRaid::scene->Add(attack, STATIC);
        MultiverseRaid::audio->Play(LASER_BEAM);
    }
    
    delete playerPoint;
}

void RobotAvatar::HandleUlt() {
}
