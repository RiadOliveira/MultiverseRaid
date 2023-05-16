#include "WizardEnemyAttack.h"
#include "MultiverseRaid.h"
#include "Vector.h"

WizardEnemyAttack::WizardEnemyAttack(float damage, WizardEnemy* origin) {
    type = ENEMY_ATTACK;
    damageType = WIZARD;
    SetDamageTickTime(1.0f);
    SetDamagePerTick(damage);

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
}

WizardEnemyAttack::~WizardEnemyAttack() {
    delete energyBall;
}

void WizardEnemyAttack::OnCollision(Object* obj) {
    uint objType = obj->Type();
    if(objType != PLAYER && objType != PLAYER_ATTACK) return;

    MultiverseRaid::scene->Delete(this, MOVING);
    if(objType == PLAYER) {
        MultiverseRaid::player->ApplyDamage(damagePerTick, WIZARD);
        MultiverseRaid::audio->Play(WIZARD_ENEMY_ATTACK);
    }
}

void WizardEnemyAttack::Update() {
    Rotate(300 * gameTime);
    Translate(speed.XComponent() * gameTime, -speed.YComponent() * gameTime);

    if (x > game->Width() - 50 || x < 50 || y > game->Height() - 50 || y < 50) {
        MultiverseRaid::scene->Delete();
    }
}