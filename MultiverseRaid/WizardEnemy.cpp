#include "WizardEnemy.h"
#include "MultiverseRaid.h"
#include "WizardEnemyAttack.h"
#include "Random.h"
#include "MultiverseRaid.h"

EntityAttributes WizardEnemy::defaultAttributes = {
    5.0f, //hp
    8.0f, //damage
    180.0f, //speed
    3.5f, //attackSpeed
    0.25f, //defense
    300.0f //range
};

EntityAttributes WizardEnemy::wizardsAttributes = {
    5.0f, //hp
    8.0f, //damage
    180.0f, //speed
    3.5f, //attackSpeed
    0.25f, //defense
    300.0f //range
};

WizardEnemy::WizardEnemy() {
    speed  = new Vector(0, 1.0f);
    hp = wizardsAttributes.hp;

    tileSet = new TileSet(
        "Resources/Wizard/WizardEnemy.png",
        (uint)320, (uint)250, 4, 8
    );
    animation = new Animation(tileSet, 0.6f, true);
    
    uint leftSequence[4] = { 0, 1, 2, 3 };
    animation->Add(LEFT, leftSequence, 4);

    uint rightSequence[4] = { 7, 6, 5, 4 };
    animation->Add(RIGHT, rightSequence, 4);

    Point vertex[20] =
    {
       Point(1, -8), Point(7, -4), Point(7,5),  Point(1, 9),
       Point(12, 16), Point(4, 21), Point(5, 34), Point(-30, 34),
       Point(-30, 26), Point(-34, 22), Point(-27, 12), Point(-34, 7),
       Point(-34, -2), Point(-32, -6), Point(-28, -6), Point(-20, -20),
       Point(-9, -20), Point(-3, -12), Point(-11, -12), Point(-10, -7)

    };
    BBox(new Poly(vertex, 20));
    type = ENEMY;
    enemyType = WIZARD;
    MultiverseRaid::remainingEnemies++;
}

WizardEnemy::~WizardEnemy() {
    MultiverseRaid::remainingEnemies--;
}

void WizardEnemy::ResetWaveAttributes() {
    wizardsAttributes.hp = defaultAttributes.hp;
    wizardsAttributes.damage = defaultAttributes.damage;
    wizardsAttributes.speed = defaultAttributes.speed;
    wizardsAttributes.attackSpeed = defaultAttributes.attackSpeed;
    wizardsAttributes.defense = defaultAttributes.defense;
    wizardsAttributes.range = defaultAttributes.range;
}

void WizardEnemy::UpdateWaveAttributes() {
    wizardsAttributes.hp += 2.0f;
    wizardsAttributes.damage += 2.5f;
    wizardsAttributes.speed += 18.0f;
    wizardsAttributes.attackSpeed -= 0.2f;

    if(wizardsAttributes.attackSpeed < 2.0f) {
        wizardsAttributes.attackSpeed = 2.0f;
    }
}

void WizardEnemy::OnCollision(Object * obj) {
    uint objType = obj->Type();

    if(objType == PLAYER || objType == ENEMY) {
        HandleEntityCollision(obj, wizardsAttributes.speed);
        return;
    }
    if(objType != PLAYER_ATTACK) return;

    Attack* attack = (Attack*) obj;
    bool receiveIncreaseDamage = attack->DamageType() == ALIEN;
    float damageReduction = receiveIncreaseDamage ? 0.0f : wizardsAttributes.defense;
    HandlePlayerAttackCollision(attack, damageReduction);
}

void WizardEnemy::HandleAttackPlayer() {
    Player* player = MultiverseRaid::player;
    float playerX = player->X();
    float playerY = player->Y();

    float distance = Point::Distance(Point(playerX, playerY), Point(x, y));
    if(distance > wizardsAttributes.range) return;
    if(attackSpeedTimer->Elapsed() < wizardsAttributes.attackSpeed) return;

    MultiverseRaid::scene->Add(
        new WizardEnemyAttack(wizardsAttributes.damage, this),
        MOVING
    );
    attackSpeedTimer->Reset();
}

void WizardEnemy::Update() {
    if(IsDead()) {
        MultiverseRaid::scene->Delete();
        return;
    }

    HandleAttackPlayer();

    Player * player = MultiverseRaid::player;
    float angle = Line::Angle(Point(x, y), Point(player->X(), player->Y()));
    float magnitude = 20.0f * gameTime;
    Vector target = Vector(angle, magnitude);
    
    float distanceToPlayer = Point::Distance(Point(x, y), Point(player->X(), player->Y()));
    bool hasToEscape = distanceToPlayer < wizardsAttributes.range - 20.0f;
    bool hasToGetCloser = distanceToPlayer > wizardsAttributes.range;

    if(!hasToEscape && !hasToGetCloser) target.Rotate(90.0f);
    else if(hasToEscape) target.Rotate(180.0f);

    speed->Add(target);
    if (speed->Magnitude() > 1.0f) speed->ScaleTo(1.0f);

    float parsedSpeed = wizardsAttributes.speed * gameTime;
    Translate(speed->XComponent() * parsedSpeed, -speed->YComponent() * parsedSpeed);
    animation->Select(speed->XComponent() > 0 ? LEFT : RIGHT);
    animation->NextFrame();

    if (x < 50) MoveTo(50, y);
    else if (x > game->Width() - 50) MoveTo(game->Width() - 50, y);

    if (y < 50) MoveTo(x, 50);
    else if (y > game->Height() - 50) MoveTo(x, game->Height() - 50);
}
