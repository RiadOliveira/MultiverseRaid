#include "MultiverseRaid.h"
#include "RobotEnemy.h"
#include "Random.h"

EntityAttributes RobotEnemy::robotsAttributes = {
    10.0f, //hp
    5.0f, //damage
    200.0f, //speed
    3.0f, //attackSpeed
    0.40f, //defense
    30.0f //range
};

RobotEnemy::RobotEnemy() {
    sprite = new Sprite("Resources/Robot/RobotEnemy.png");
    speed  = new Vector(0, 1.0f);
    hp = robotsAttributes.hp;

    BBox(new Rect(-18.0f, -18.0f, 18.0f, 18.0f));
    RandF posX{ 300, 400 };
    RandF posY{ game->Height() - 400, game->Height() - 300 };
    MoveTo(posX.Rand(), posY.Rand());

    type = ENEMY;
    enemyType = ROBOT;
}

RobotEnemy::~RobotEnemy() {
}

void RobotEnemy::UpdateWaveAttributes() {
    robotsAttributes.hp += 2.0f;
    robotsAttributes.damage += 0.5f;
    robotsAttributes.speed += 15.0f;
    robotsAttributes.attackSpeed -= 0.2f;

    if(robotsAttributes.attackSpeed < 1.5f) {
        robotsAttributes.attackSpeed = 1.5f;
    }
}

void RobotEnemy::OnCollision(Object * obj) {
    if(obj->Type() == PLAYER) {
        HandlePlayerCollision(
            robotsAttributes.damage,
            robotsAttributes.attackSpeed
        );
        return;
    };
    if(obj->Type() != PLAYER_ATTACK) return;

    PlayerAttack* attack = (PlayerAttack*) obj;
    bool receiveIncreaseDamage = attack->DamageType() == WIZARD;
    float damageReduction = receiveIncreaseDamage ? 0.0f : robotsAttributes.defense;

    HandlePlayerAttackCollision(attack, damageReduction);
}

void RobotEnemy::Update() {
    if(IsDead()) {
        MultiverseRaid::scene->Delete();
        return;
    }

    Player * player = MultiverseRaid::player;
    speed->RotateTo(Line::Angle(Point(x, y), Point(player->X(), player->Y())));
    float distanceToPlayer = Point::Distance(Point(x, y), Point(player->X(), player->Y()));

    if(distanceToPlayer > robotsAttributes.range) {
        float parsedSpeed = robotsAttributes.speed * gameTime;
        Translate(speed->XComponent() * parsedSpeed, -speed->YComponent() * parsedSpeed);
    }
}
