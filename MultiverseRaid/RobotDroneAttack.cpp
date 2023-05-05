#include "RobotDroneAttack.h"
#include "MultiverseRaid.h"
#include "Vector.h"

RobotDroneAttack::RobotDroneAttack(float damage, RobotDrone* drone, Object* target) {
    damageType = ROBOT;
    damageTickTime = 2.0f;
    damagePerTick = damage;

    float tileWidth = 22.0f, halfTileWidth = tileWidth/2;
    float tileHeight = 16.0f, halfTileHeight = tileHeight/2;
    float distanceFromDrone = 28.0f + halfTileHeight;

    energyBall = new TileSet(
        "Resources/Robot/RobotDroneAttack.png",
        (uint) tileWidth, (uint) tileHeight, 3, 3
    );
    animation = new Animation(energyBall, 0.060f, true);
    uint sequence[3] = {0, 1, 2};
    animation->Add(0, sequence, 3);

    float angle = Line::Angle(
        Point(drone->X(), drone->Y()),
        Point(target->X(), target->Y())
    );
    speed = new Vector(angle, 1.0f);
    speed->Scale(distanceFromDrone);

    MoveTo(
        drone->X() + speed->XComponent(),
        drone->Y() - speed->YComponent()
    );
    Rotate(-(angle + 90.0f));

    speed->ScaleTo(400.0f);
    BBox(new Circle(tileHeight));
}

RobotDroneAttack::~RobotDroneAttack() {
    delete energyBall;
    delete animation;
    delete speed;
}

void RobotDroneAttack::Update() {
    animation->NextFrame();
    Translate(speed->XComponent() * gameTime, -speed->YComponent() * gameTime);

    if (x > game->Width() - 50 || x < 50 || y > game->Height() - 50 || y < 50) {
        MultiverseRaid::scene->Delete();
    }
}