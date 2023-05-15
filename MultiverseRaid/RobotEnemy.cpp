#include "MultiverseRaid.h"
#include "RobotEnemy.h"

EntityAttributes RobotEnemy::defaultAttributes = {
    10.0f, //hp
    5.0f, //damage
    180.0f, //speed
    3.0f, //attackSpeed
    0.40f, //defense
    30.0f //range
};

EntityAttributes RobotEnemy::robotsAttributes = {
    10.0f, //hp
    5.0f, //damage
    180.0f, //speed
    3.0f, //attackSpeed
    0.40f, //defense
    30.0f //range
};

RobotEnemy::RobotEnemy() {
    speed  = new Vector(0, 1.0f);
    hp = robotsAttributes.hp;

    Point vertex[24] =
    {
        Point(11, -37), Point(11, -26), Point(18, -26), Point(18, -5),
        Point(13, -5), Point(13, 4), Point(25, 4), Point(25, 33),
        Point(13, 33), Point(13, 8), Point(5, 18), Point(5, 37),
        Point(-7, 37), Point(-7, 18), Point(-13, 8), Point(-13, 33),
        Point(-25,33), Point(-25,4), Point(-13, 4), Point(-13, -5),
        Point(-16, -5), Point(-16, -26), Point(-11, -26), Point(-11, -37)
    };
    BBox(new Poly(vertex, 24));

    tileSet = new TileSet(
        "Resources/Robot/RobotEnemy.png",
        (uint)252, (uint)300, 4, 1
    );
    animation = new Animation(tileSet, 0.2f, true);
    uint sequence[4] = { 0, 1, 2, 3 };
    animation->Add(0, sequence, 4);

    type = ENEMY;
    enemyType = ROBOT;
    MultiverseRaid::remainingEnemies++;
}

RobotEnemy::~RobotEnemy() {
    MultiverseRaid::remainingEnemies--;
}

void RobotEnemy::ResetWaveAttributes() {
    robotsAttributes.hp = defaultAttributes.hp;
    robotsAttributes.damage = defaultAttributes.damage;
    robotsAttributes.speed = defaultAttributes.speed;
    robotsAttributes.attackSpeed = defaultAttributes.attackSpeed;
    robotsAttributes.defense = defaultAttributes.defense;
    robotsAttributes.range = defaultAttributes.range;
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

    Attack* attack = (Attack*) obj;
    bool receiveIncreaseDamage = attack->DamageType() == WIZARD;
    float damageReduction = receiveIncreaseDamage ? 0.0f : robotsAttributes.defense;

    HandlePlayerAttackCollision(attack, damageReduction);
}

void RobotEnemy::Update() {
    animation->NextFrame();
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
