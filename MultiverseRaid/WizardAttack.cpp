#include "WizardAttack.h"
#include "MultiverseRaid.h"
#include "Vector.h"

WizardAttack::WizardAttack(float damage, Object* target) {
    damageType = WIZARD;
    damageTickTime = 1.0f;
    damagePerTick = damage;

    Player* player = MultiverseRaid::player;
    float posX = player->X();
    float posY = player->Y();

    fireBall = new TileSet(
        "Resources/Wizard/FireBallAttack.png",
        (uint) 16, (uint) 16, 4, 4
    );
    animation = new Animation(fireBall, 0.090f, true);
    uint sequence[4] = {0, 1, 2, 3};
    animation->Add(0, sequence, 4);

    float angle = Line::Angle(
        Point(posX, posY), Point(target->X(), target->Y())
    );
    
    speed.RotateTo(angle);
    speed.ScaleTo(540.0f);
    
    MoveTo(posX + 22 * cos(speed.Radians()), posY - 22 * sin(speed.Radians()));
    RotateTo(-angle + 90.0f);
    BBox(new Circle(22.0f));
}

WizardAttack::~WizardAttack() {
    delete fireBall;
    delete animation;
}

void WizardAttack::Update() {
    Translate(speed.XComponent()* gameTime, -speed.YComponent()* gameTime);
    animation->NextFrame();

    if (x > game->Width() - 50 || x < 50 || y > game->Height() - 50 || y < 50) {
        MultiverseRaid::scene->Delete();
    }
}