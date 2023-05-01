#include "MultiverseRaid.h"
#include "RobotEnemy.h"
#include "Random.h"

EntityAttributes RobotEnemy::robotsAttributes = {
    10.0f, //hp
    200.0f, //speed
    5.0f, //damage
    3.0f, //attackSpeed
    0.40f //defense
};

RobotEnemy::RobotEnemy(Player * p) : player (p), hp(robotsAttributes.hp) {
    sprite = new Sprite("Resources/RobotEnemy.png");
    speed  = new Vector(0, 2.0f);
    BBox(new Circle(18.0f));
    
    RandF posX{ 300, 400 };
    RandF posY{ game->Height() - 400, game->Height() - 300 };
    MoveTo(posX.Rand(), posY.Rand());

    type = ROBOT_ENEMY;
}

RobotEnemy::~RobotEnemy() {
    delete sprite;
    delete speed;
}

void RobotEnemy::UpdateWaveAttributes() {
    robotsAttributes.hp += 2.0f;
    robotsAttributes.speed += 15.0f;
    robotsAttributes.damage += 0.5f;
    robotsAttributes.attackSpeed -= 0.2f;

    if(robotsAttributes.attackSpeed < 1.5f) {
        robotsAttributes.attackSpeed = 1.5f;
    }
}

void RobotEnemy::OnCollision(Object * obj) {
    if (obj->Type() == MISSILE) MultiverseRaid::scene->Delete(this, MOVING);
}

void RobotEnemy::Update() {
    speed->RotateTo(Line::Angle(Point(x, y), Point(player->X(), player->Y())));

    float parsedSpeed = robotsAttributes.speed * gameTime;
    Translate(speed->XComponent() * parsedSpeed, -speed->YComponent() * parsedSpeed);
}
