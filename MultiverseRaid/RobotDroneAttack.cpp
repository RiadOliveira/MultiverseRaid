#include "RobotDroneAttack.h"
#include "MultiverseRaid.h"
#include "Vector.h"

RobotDroneAttack::RobotDroneAttack(
    float damage, float angle, RobotDrone* drone
) {
    damageType = ROBOT;
    damageTickTime = 2.0f;
    damagePerTick = damage;
    sprite = new Sprite("Resources/Robot/RobotDroneAttack.png");

    float posX = drone->X();
    float posY = drone->Y();
    speed.RotateTo(angle);
    speed.ScaleTo(460.0f);
    
    startPoint = Point(
        posX + 22 * cos(speed.Radians()),
        posY - 22 * sin(speed.Radians())
    );

    MoveTo(startPoint.X(), startPoint.Y());
    RotateTo(-angle);
    BBox(new Circle(9.0f));

    type = PLAYER_ATTACK;
}

RobotDroneAttack::~RobotDroneAttack() {
    delete sprite;
}

void RobotDroneAttack::Update() {
    Translate(speed.XComponent() * gameTime, -speed.YComponent() * gameTime);

    bool outOfGame = x > game->Width() - 50 || x < 50 || y > game->Height() - 50 || y < 50;
    bool outOfRange = Point::Distance(startPoint, Point(x, y)) >= 123.0f;
    if (outOfGame || outOfRange) MultiverseRaid::scene->Delete();
}