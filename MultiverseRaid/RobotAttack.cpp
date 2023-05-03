#include "RobotAttack.h"
#include "MultiverseRaid.h"
#include "Vector.h"

RobotAttack::RobotAttack(float posX, float posY, Object* target) {
    BBox(new Rect(-12.5f, -140.5f, 12.5f, 140.5f));
    
    laserBeam = new TileSet("Resources/RobotAttack.png", 25, 65, 3, 3);
    animation = new Animation(laserBeam, 0.060f, false);

    uint sequence[3] = {0, 1, 2};
    animation->Add(0, sequence, 3);

    Point centerPoint = Point(posX, posY);
    Point targetPoint = Point(target->X(), target->Y());

    float angle = Line::Angle(centerPoint, targetPoint);
    Vector vector = Vector(angle, 1.0f);
    vector.Scale(48.0f);

    MoveTo(posX + vector.XComponent(), posY - vector.YComponent());
    Rotate(-(angle + 90.0f));
}

RobotAttack::~RobotAttack() {
    delete laserBeam;
    delete animation;
}

void RobotAttack::Update() {
    Player * player = MultiverseRaid::player;
    Point playerCenter = Point(player->X(), player->Y());
    Point attackCenter = Point(x, y);

    float angle = Line::Angle(playerCenter, attackCenter);
    float distance = Point::Distance(playerCenter, attackCenter);

    Vector vector = Vector(angle, 48.0f - distance);
    Translate(vector.XComponent(), -vector.YComponent());

    if(animation->Inactive()) MultiverseRaid::scene->Delete();
    else animation->NextFrame();
}