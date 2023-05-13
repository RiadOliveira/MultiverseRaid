#include "RobotDroneAttack.h"
#include "MultiverseRaid.h"
#include "Vector.h"

RobotDroneAttack::RobotDroneAttack(
    Image* energyBall, float damage,
    RobotDrone* drone, Object* target
) {
    damageType = ROBOT;
    damageTickTime = 2.0f;
    damagePerTick = damage;
    sprite = new Sprite(energyBall);

    float posX = drone->X();
    float posY = drone->Y();

    float angle = Line::Angle(
        Point(posX, posY),
        Point(target->X(), target->Y())
    );
    
    speed.RotateTo(angle);
    speed.ScaleTo(460.0f);
    
    MoveTo(posX + 22 * cos(speed.Radians()), posY - 22 * sin(speed.Radians()));
    RotateTo(-angle + 90.0f);
    BBox(new Circle(14.0f));
}

RobotDroneAttack::~RobotDroneAttack() {
    delete sprite;
}

void RobotDroneAttack::Update() {
    Rotate(300 * gameTime);
    Translate(speed.XComponent() * gameTime, -speed.YComponent() * gameTime);

    if (x > game->Width() - 50 || x < 50 || y > game->Height() - 50 || y < 50) {
        MultiverseRaid::scene->Delete();
    }
}