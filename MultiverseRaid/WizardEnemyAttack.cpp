#include "WizardEnemyAttack.h"
#include "MultiverseRaid.h"
#include "Vector.h"

WizardEnemyAttack::WizardEnemyAttack(
    float damage, WizardEnemy* origin
) {
    damageType = WIZARD;
    damageTickTime = 1.0f;
    damagePerTick = damage;
    energyBall = new Sprite("Resources/Wizard/EnergyBall.png");

    Player* player = MultiverseRaid::player;
    float targetX = player->X(), targetY = player->Y();
    float posX = origin->X(), posY = origin->Y();

    float angle = Line::Angle(
        Point(posX, posY),
        Point(targetX, targetY)
    );
    
    speed.RotateTo(angle);
    speed.ScaleTo(460.0f);
    
    MoveTo(posX + 22 * cos(speed.Radians()), posY - 22 * sin(speed.Radians()));
    RotateTo(-angle + 90.0f);
    BBox(new Circle(14.0f));

    type = ENEMY_ATTACK;
}

WizardEnemyAttack::~WizardEnemyAttack() {
    delete energyBall;
}

void WizardEnemyAttack::OnCollision(Object* obj) {
    if(obj->Type() != PLAYER) return;

    MultiverseRaid::player->ApplyDamage(damagePerTick, WIZARD);
    MultiverseRaid::scene->Delete(this, MOVING);
}

void WizardEnemyAttack::Update() {
    Rotate(300 * gameTime);
    Translate(speed.XComponent() * gameTime, -speed.YComponent() * gameTime);

    if (x > game->Width() - 50 || x < 50 || y > game->Height() - 50 || y < 50) {
        MultiverseRaid::scene->Delete();
    }
}