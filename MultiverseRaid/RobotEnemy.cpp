#include "MultiverseRaid.h"
#include "RobotEnemy.h"
#include "Random.h"

EntityAttributes RobotEnemy::robotsAttributes = {
    10.0f, //hp
    200.0f, //speed
    5.0f, //damage
    3.0f, //attackSpeed
    0.40f, //defense
    30.0f //range
};

RobotEnemy::RobotEnemy(): hp(robotsAttributes.hp) {
    sprite = new Sprite("Resources/RobotEnemy.png");
    speed  = new Vector(0, 1.0f);
    BBox(new Circle(18.0f));
    
    RandF posX{ 300, 400 };
    RandF posY{ game->Height() - 400, game->Height() - 300 };
    MoveTo(posX.Rand(), posY.Rand());

    type = ROBOT_ENEMY;
}

RobotEnemy::~RobotEnemy() {
    delete sprite;
    delete speed;
    delete attackSpeedTimer;
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
    if(obj->Type() != PLAYER) return;
    Player * player = MultiverseRaid::player;

    bool isFirstPlayerCollision = attackSpeedTimer == nullptr;
    if(isFirstPlayerCollision) {
        player->ApplyDamage(robotsAttributes.damage);
        attackSpeedTimer = new Timer();
        attackSpeedTimer->Start();

        return;
    }

    bool attackOnCooldown = attackSpeedTimer->Elapsed() < robotsAttributes.attackSpeed;
    if(attackOnCooldown) return;

    player->ApplyDamage(robotsAttributes.damage);
    attackSpeedTimer->Start();
}

void RobotEnemy::Update() {
    Player * player = MultiverseRaid::player;
    speed->RotateTo(Line::Angle(Point(x, y), Point(player->X(), player->Y())));

    float distanceToPlayer = Point::Distance(Point(x, y), Point(player->X(), player->Y()));

    if(distanceToPlayer > robotsAttributes.range) {
        float parsedSpeed = robotsAttributes.speed * gameTime;
        Translate(speed->XComponent() * parsedSpeed, -speed->YComponent() * parsedSpeed);
    }
}
