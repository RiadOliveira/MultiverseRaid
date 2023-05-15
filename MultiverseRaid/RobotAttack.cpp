#include "RobotAttack.h"
#include "MultiverseRaid.h"
#include "Vector.h"

RobotAttack::RobotAttack(float damage, Object* target) {
    damageType = ROBOT;
    damageTickTime = 1.0f;
    damagePerTick = damage;

    Player* player = MultiverseRaid::player;
    float posX = player->X();
    float posY = player->Y();

    float tileWidth = 24.0f, halfTileWidth = tileWidth/2;
    float tileHeight = 270.0f, halfTileHeight = tileHeight/2;
    float distanceFromPlayer = 18.0f + halfTileHeight;

    laserBeam = new TileSet(
        "Resources/Robot/RobotAttack.png",
        (uint) tileWidth, (uint) tileHeight, 6, 6
    );
    animation = new Animation(laserBeam, 0.16f, false);
    uint sequence[6] = {0, 1, 2, 3, 4, 5};
    animation->Add(0, sequence, 6);

    angle = Line::Angle(
        Point(posX, posY), Point(target->X(), target->Y())
    );
    Vector vector = Vector(angle, distanceFromPlayer);

    MoveTo(
        posX + vector.XComponent(), posY - vector.YComponent()
    );
    Rotate(-(angle + 90.0f));

    Point p1 = Point(-halfTileWidth, -halfTileHeight);
    Point p2 = Point(halfTileWidth, -halfTileHeight);
    float laserEnd = 288.0f - distanceFromPlayer;
    Point p3 = Point(halfTileWidth, laserEnd);
    Point p4 = Point(-halfTileWidth, laserEnd);

    Point list[4] = {p1, p2, p3, p4};
    BBox(new Poly(list, 4));

    type = PLAYER_ATTACK;
}

RobotAttack::~RobotAttack() {
    delete animation;
}

void RobotAttack::Update() {
    Player * player = MultiverseRaid::player;
    float posX = player->X();
    float posY = player->Y();

    Vector vector = Vector(angle, 153.0f);
    MoveTo(
        posX + vector.XComponent(), posY - vector.YComponent()
    );

    if(animation->Inactive()) MultiverseRaid::scene->Delete();
    else animation->NextFrame();
}